#include "Define.h"
#include "GameCenter.h"
#include <cmath>
#include <cstdlib>

// update -> render -> 충돌 처리
// object로 player, item 관리 ,,, 나중에 추가할때 index만 따와서 할수있게끔


GameCenter::GameCenter()
	: m_hWnd(0), m_ptResolution{0,0}, m_hdc(0), rectView()
{
	setPlayer(player);
	addItem();
	CreateBitmap();
}

GameCenter::~GameCenter()
{
	DeleteBitmap();
}

void GameCenter::Update()
{
	DrawBitmapDoubleBuffering(m_hWnd, m_hdc);
	
	player.UpdatePlayer();
	OnCollision();
	isMining(m_hWnd);
}

int GameCenter::Init(HWND g_hWnd, POINT p)
{
	m_hWnd = g_hWnd;
	m_ptResolution = p;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 500, 200, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(m_hWnd);

	GetClientRect(m_hWnd, &rectView);

	return MB_OK;
}


int GameCenter::isMining(HWND hWnd)
{
	player.Click(hWnd);

	//if (abs(player.getPosition().x - player.getCursorPos().x) <= 50 && abs(player.getPosition().y - player.getCursorPos().y) <= 50)
	{
		//cout << "near" << endl;
		for (auto it = itemList.begin(); it != itemList.end(); it++)
		{
			if ((*it)->getPositionX() - 4 <= player.getCursorPos().x && player.getCursorPos().x <= (*it)->getPositionX() + 34)
			{
				if ((*it)->getPositionY() <= player.getCursorPos().y && player.getCursorPos().y <= (*it)->getPositionY() + 32)
				{
					// 아이템 삭제
					if ((*it)->getMineCount() == 2)
					{
						(*it)->setMineCount(0);
						delete (*it);
						return 3;
					}
					else if ((*it)->getMineCount() == 0)
					{
						(*it)->setMineCount(1);
						return 1;
					}
					else if ((*it)->getMineCount() == 1)
					{
						(*it)->setMineCount(2);
						return 2;
					}
				}
			}
		}
	}

	return 0;
	
}

void GameCenter::addItem()
{
	// 랜덤으로 줄시 겹치는 경우 발생
	srand(time(NULL));

	Item* i1 = new Item({ 200, 200 }, stone1);
	itemList.push_back(i1);

	Item* i2 = new Item({ 250, 250 }, stone1);
	itemList.push_back(i2);

	Item* i3 = new Item({ 350, 350 }, stone2);
	itemList.push_back(i3);

	Item* i4 = new Item({ 400, 400 }, stone2);
	itemList.push_back(i4);
}

void GameCenter::deleteItem()
{

}


void GameCenter::OnCollision()
{
	for (auto it = itemList.begin(); it != itemList.end(); it++)
	{
		// x축
		if (player.getStartRect().x - 2 < (*it)->getEndRect().x && (*it)->getStartRect().x < player.getEndRect().x + 2)
		{
			if (player.getStartRect().y - 2  < (*it)->getEndRect().y && player.getEndRect().y + 2 > (*it)->getStartRect().y )
			{
				cout << "collided! " << player.getCollidedDir() << endl;
				player.setCollided(true, player.getViewDir());
				player.setPrevPosition(player.getPosition());
			}
			else
			{
				player.setCollided(false, player.getpreViewDir());
			}
		}
		// y축
		if (player.getStartRect().y - 2 < (*it)->getEndRect().y && player.getEndRect().y + 2 > (*it)->getStartRect().y)
		{
			if (player.getStartRect().x - 2 < (*it)->getEndRect().x && (*it)->getStartRect().x < player.getEndRect().x + 2)
			{
				cout << "collided! " << player.getCollidedDir() << endl;
				player.setCollided(true, player.getViewDir());
				player.setPrevPosition(player.getPosition());
			}
			else
			{
				player.setCollided(false, player.getpreViewDir());
			}
		}
	}
	
}

void GameCenter::CreateBitmap()
{
	// >> : map
	{
		hMapImage = (HBITMAP)LoadImage(NULL, TEXT("images/map.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hMapImage == NULL) // 이미지가 출력되지 않을 때
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, TEXT("맵 이미지 로드 에러"), TEXT("에러"), MB_OK);
			return;
		}

		GetObject(hMapImage, sizeof(BITMAP), &bitMap);
	}

	player.CreateBitmap();
	itemList.front()->CreateBitmap();
}

void GameCenter::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  기본은 검정색

	// map
	{
		hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hMapImage);
		bx = bitMap.bmWidth; // 전체 너비
		by = bitMap.bmHeight; // 전체 높이

		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
	}

	// player & item
	player.DrawBitmapDoubleBuffering(m_hWnd, hMemDC);
	for (auto it = itemList.begin(); it != itemList.end(); it++)
		(*it)->DrawBitmapDoubleBuffering(m_hWnd, hMemDC);

	// object 그리드
	{
		HBRUSH hBrush, oldBrush;
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		HPEN hPen, oldPen;
		hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hMemDC, hPen);

		Rectangle(hMemDC, player.getStartRect().x, player.getStartRect().y, player.getEndRect().x, player.getEndRect().y);
		for (auto it = itemList.begin(); it != itemList.end(); it++)
			Rectangle(hMemDC, (*it)->getStartRect().x, (*it)->getStartRect().y, (*it)->getEndRect().x, (*it)->getEndRect().y);

		DeleteObject(hBrush);
		DeleteObject(hPen);
	}

	// >> : hdc에 그려주기
	TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void GameCenter::DeleteBitmap()
{
	DeleteObject(hMapImage);
	player.DeleteBitmap();
	itemList.front()->DeleteBitmap();
}

void GameCenter::UpdateFrame(HWND hWnd)
{
	curframe++;
	if (curframe > RUN_FRAME_MAX)
		curframe = RUN_FRAME_MIN;
}

VOID CALLBACK GameCenter::AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (getPlayer().getViewDir() != PAUSE/* && idEvent == timer_ID_1*/)
	{
		UpdateFrame(hWnd);
	}
}