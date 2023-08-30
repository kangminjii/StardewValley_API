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
	CreateBitmap(m_hdc);
}

GameCenter::~GameCenter()
{
	DeleteBitmap();
}

void GameCenter::Update()
{
	if (startScene)
	{
		StartScene(m_hdc);
		POINT curPos;
		GetCursorPos(&curPos);
		ScreenToClient(m_hWnd, &curPos);
		
		if ((curPos.x >= 400 && curPos.x <= 600) && (curPos.y >= 500 && curPos.y <= 600))
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 클릭하면 다음 씬으로 넘어가기
			{
				startScene = false;
				DeleteObject(hStartImage);
				DeleteObject(hBackImage);
			}
			else // 아닐시 버튼 깜빡거리기
			{
				isTouched = true;
			}
		}
		else
			isTouched = false;
	}
	else
	{
		DrawBitmapDoubleBuffering(m_hdc);

		player.UpdatePlayer();
		OnCollision();
		isMining(m_hWnd);
	}
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

	// 일정 프레임 이후에 돌이 삭제됨
	if (player.getMineCheck())
	{
		cout << "itemlist size : " << itemList.size() << endl;
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
	// 랜덤한 타일맵에 아이템 배치
	srand(time(NULL));

	vector<vector<POINT>> tiles(ROW, vector<POINT>(COL));
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			tiles[i][j] = { 40 * j, 40 * i };
		}
	}

	for (int i = 9; i < 16; i++) // 행
	{
		for (int j = 8; j < 17; j++) // 열
		{
			int random = rand() % 5; // 0~4
			int stoneType = rand() % 3; // 0~2

			if (random == 0)
			{
				Item* i1 = new Item({ tiles[i][j].x, tiles[i][j].y }, stoneType);
				itemList.push_back(i1);
			}
		}
	}
}

void GameCenter::deleteItem()
{
}


void GameCenter::OnCollision()
{
	for (auto it = itemList.begin(); it != itemList.end(); it++)
	{
		// IntersectRect 함수로 확인하는 방법
		static RECT tmpRect;
		LPRECT playerRect = player.getRect();
		LPRECT itemRect = (*it)->getRect();
		if (IntersectRect(&tmpRect, playerRect, itemRect))
		{
			player.setCollided(true, player.getViewDir());
			//cout << "collided! " << player.getCollidedDir() << endl;

			player.setPrevPosition(player.getPosition());
		}
		
		// 사각형 x, y좌표로 확인하는 방법
		//// x축
		//if (player.getStartRect().x < (*it)->getEndRect().x && (*it)->getStartRect().x < player.getEndRect().x)
		//{
		//	if (player.getStartRect().y < (*it)->getEndRect().y && player.getEndRect().y > (*it)->getStartRect().y )
		//	{
		//		cout << "collided! " << endl;
		//		player.setCollided(true, player.getViewDir());
		//		player.setPrevPosition(player.getPosition());
		//	}
		//}
		//// y축
		//if (player.getStartRect().y - 2 < (*it)->getEndRect().y && player.getEndRect().y + 2 > (*it)->getStartRect().y)
		//{
		//	if (player.getStartRect().x - 2 < (*it)->getEndRect().x && (*it)->getStartRect().x < player.getEndRect().x + 2)
		//	{
		//		cout << "collided! " << endl;
		//		player.setCollided(true, player.getViewDir());
		//		player.setPrevPosition(player.getPosition());
		//	}
		//}
	}
}

void GameCenter::CreateBitmap(HDC hdc)
{
	// inventory
	{
		hInvenImage = (HBITMAP)LoadImage(NULL, TEXT("images/inventory.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hInvenImage == NULL) // 이미지가 출력되지 않을 때
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, TEXT("인벤토리 이미지 로드 에러"), TEXT("에러"), MB_OK);
			return;
		}

		GetObject(hInvenImage, sizeof(BITMAP), &bitInven);
	}
	
	// start scene
	{
		hStartImage = (HBITMAP)LoadImage(NULL, TEXT("images/startScene.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hStartImage == NULL) // 이미지가 출력되지 않을 때
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, TEXT("시작 이미지 로드 에러"), TEXT("에러"), MB_OK);
			return;
		}
		GetObject(hStartImage, sizeof(BITMAP), &bitStart);
	}

	// start Background scene
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/startBack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hBackImage == NULL) // 이미지가 출력되지 않을 때
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, TEXT("시작 배경 이미지 로드 에러"), TEXT("에러"), MB_OK);
			return;
		}
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}

}

void GameCenter::DrawBitmapDoubleBuffering(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap, hInvenBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  기본은 검정색

	// map
	//tilemap.DrawBitmapDoubleBuffering(hMemDC);
	tile.PaintTile(hMemDC);
	
	// item
	for (auto it = itemList.begin(); it != itemList.end(); it++)
		(*it)->DrawBitmapDoubleBuffering(hMemDC);

	// player
	player.DrawBitmapDoubleBuffering(hMemDC);

	// 인벤토리
	HDC hMemDC2 = CreateCompatibleDC(hMemDC);
	{
		hInvenBitmap = (HBITMAP)SelectObject(hMemDC2, hInvenImage);
		TransparentBlt(hMemDC, 200, 700, 600, 80, hMemDC2, 0, 0, bitInven.bmWidth, bitInven.bmHeight, RGB(0, 0, 0));
		SelectObject(hMemDC2, hInvenBitmap);
		DeleteDC(hMemDC2);
	}

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
		for (int i = 3; i < 18; i++)
		{
			for (int j = 5; j < 20; j++)
			{
				//Rectangle(hMemDC, tilemap.getTiles()[i][j].x - 20, tilemap.getTiles()[i][j].y - 20, tilemap.getTiles()[i][j].x + 20, tilemap.getTiles()[i][j].y + 20);
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
	tile.DeleteTile();
	player.DeleteBitmap();
	itemList.front()->DeleteBitmap();
	DeleteObject(hInvenImage);
}

void GameCenter::StartScene(HDC hdc)
{
	HBITMAP hOldBitmap, hStartBitmap, hBackBitmap;

	HDC hMemDC = CreateCompatibleDC(hdc);

	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  기본은 검정색

	// draw
	HDC hMemDC2 = CreateCompatibleDC(hMemDC);

	hBackBitmap = (HBITMAP)SelectObject(hMemDC2, hBackImage);
	TransparentBlt(hMemDC, 0, 0, 1000, 800, hMemDC2, 0, 0, bitBack.bmWidth, bitBack.bmHeight, RGB(0, 0, 0));


	hStartBitmap = (HBITMAP)SelectObject(hMemDC2, hStartImage);
	TransparentBlt(hMemDC, 200, 100, 600, 270, hMemDC2, 0, 0, 400, 185, RGB(0, 0, 0));
	if(!isTouched)
		TransparentBlt(hMemDC, 400, 500, 150, 100, hMemDC2, 0, 187, 70, 57, RGB(0, 0, 0));
	else
		TransparentBlt(hMemDC, 400, 500, 150, 100, hMemDC2, 0, 244, 70, 57, RGB(0, 0, 0));

	SelectObject(hMemDC2, hStartBitmap);
	DeleteDC(hMemDC2);

	TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(0,0,0));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}