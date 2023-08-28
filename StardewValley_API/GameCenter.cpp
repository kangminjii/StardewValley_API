#include "Define.h"
#include "GameCenter.h"
#include <cmath>
#include <cstdlib>

// update -> render -> 충돌 처리
// object로 player, item 관리 ,,, 나중에 추가할때 index만 따와서 할수있게끔


GameCenter::GameCenter()
	: m_hWnd(0), m_ptResolution{0,0}, m_hdc(0), rectView()
{
	addItem();
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

void GameCenter::isMining(HWND hWnd)
{
	player.Click(hWnd);
	if (player.getMineCheck())
	{
		for (auto it = itemList.begin(); it != itemList.end(); it++)
		{
			if ((*it)->getPosition().x - 4 <= player.getCursorPos().x && player.getCursorPos().x <= (*it)->getPosition().x + 34)
			{
				if ((*it)->getPosition().y <= player.getCursorPos().y && player.getCursorPos().y <= (*it)->getPosition().y + 32)
				{
					// 아이템 삭제
					player.setMineCheck(false);
					delete (*it);
				}
			}
		}
	}

	// 거리 내에 있는 돌만 캘수 있게끔 범위 설정
	//if (abs(player.getPosition().x - player.getCursorPos().x) <= 50 && abs(player.getPosition().y - player.getCursorPos().y) <= 50)
	{
		//cout << "near" << endl;
		
	}
}

void GameCenter::addItem()
{
	// 랜덤으로 줄시 겹치는 경우 발생
	srand(time(NULL));

	/*Item* i1 = new Item({ 200, 200 }, stone1);
	itemList.push_back(i1);

	Item* i2 = new Item({ 250, 250 }, stone1);
	itemList.push_back(i2);

	Item* i3 = new Item({ 350, 350 }, stone2);
	itemList.push_back(i3);*/

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

void GameCenter::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  기본은 검정색
	
	// map
	tilemap.DrawBitmapDoubleBuffering(hMemDC);

	// player & item
	player.DrawBitmapDoubleBuffering(hMemDC);
	for (auto it = itemList.begin(); it != itemList.end(); it++)
		(*it)->DrawBitmapDoubleBuffering(hMemDC);

	// object 그리드
	{
		HBRUSH hBrush, oldBrush;
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		HPEN hPen, oldPen;
		hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hMemDC, hPen);

		//Rectangle(hMemDC, player.getStartRect().x, player.getStartRect().y, player.getEndRect().x, player.getEndRect().y);
		for (auto it = itemList.begin(); it != itemList.end(); it++)
			Rectangle(hMemDC, (*it)->getStartRect().x, (*it)->getStartRect().y, (*it)->getEndRect().x, (*it)->getEndRect().y);
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				//Rectangle(hMemDC, tilemap.getTiles()[i][j].x + 150, tilemap.getTiles()[i][j].y + 100, tilemap.getTiles()[i][j].x + 190, tilemap.getTiles()[i][j].y + 140);
			}
		}

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
	tilemap.DeleteBitmap();
	player.DeleteBitmap();
	itemList.front()->DeleteBitmap();
}