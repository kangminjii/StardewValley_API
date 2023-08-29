#include "Define.h"
#include "GameCenter.h"
#include <cmath>
#include <cstdlib>

// update -> render -> �浹 ó��
// object�� player, item ���� ,,, ���߿� �߰��Ҷ� index�� ���ͼ� �Ҽ��ְԲ�


GameCenter::GameCenter()
	: m_hWnd(0), m_ptResolution{0,0}, m_hdc(0), rectView()
{
	addItem();
	// inventory

	hInvenImage = (HBITMAP)LoadImage(NULL, TEXT("images/inventory.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hInvenImage == NULL) // �̹����� ��µ��� ���� ��
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, TEXT("�κ��丮 �̹��� �ε� ����"), TEXT("����"), MB_OK);
		return;
	}

	GetObject(hInvenImage, sizeof(BITMAP), &bitInven);
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

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		//tilemap.SaveTile();
		SaveTile();
	}

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		//tilemap.LoadTile();
		LoadTile();
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

	// ���� ������ ���Ŀ� ���� ������
	if (player.getMineCheck())
	{
		cout << "itemlist size : " << itemList.size() << endl;
		for (auto it = itemList.begin(); it != itemList.end(); it++)
		{
			if ((*it)->getPosition().x - 4 <= player.getCursorPos().x && player.getCursorPos().x <= (*it)->getPosition().x + 34)
			{
				if ((*it)->getPosition().y <= player.getCursorPos().y && player.getCursorPos().y <= (*it)->getPosition().y + 32)
				{
					// ������ ����
					player.setMineCheck(false);
					delete (*it);
				}
			}
		}
	}

	
	// �Ÿ� ���� �ִ� ���� Ķ�� �ְԲ� ���� ����
	//if (abs(player.getPosition().x - player.getCursorPos().x) <= 50 && abs(player.getPosition().y - player.getCursorPos().y) <= 50)
	{
		//cout << "near" << endl;
		
	}
}

void GameCenter::addItem()
{
	// ������ Ÿ�ϸʿ� ������ ��ġ
	srand(time(NULL));

	for (int i = 9; i < 16; i++) // ��
	{
		for (int j = 8; j < 17; j++) // ��
		{
			int random = rand() % 5; // 0, 1, 2, 3, 4
			int stoneType = rand() % 3; // 0, 1, 2

			if (random == 0)
			{
				Item* i1 = new Item({ tilemap.getTiles()[i][j].x, tilemap.getTiles()[i][j].y }, stoneType);
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
		// x��
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
		// y��
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
	HBITMAP hOldBitmap, hInvenBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  �⺻�� ������

	// map
	tilemap.DrawBitmapDoubleBuffering(hMemDC);

	// item
	for (auto it = itemList.begin(); it != itemList.end(); it++)
		(*it)->DrawBitmapDoubleBuffering(hMemDC);

	// player
	player.DrawBitmapDoubleBuffering(hMemDC);

	// �κ��丮
	HDC hMemDC2 = CreateCompatibleDC(hMemDC);
	{
		hInvenBitmap = (HBITMAP)SelectObject(hMemDC2, hInvenImage);
		TransparentBlt(hMemDC, 200, 700, 600, 80, hMemDC2, 0, 0, bitInven.bmWidth, bitInven.bmHeight, RGB(0, 0, 0));
		SelectObject(hMemDC2, hInvenBitmap);
		DeleteDC(hMemDC2);
	}

	// object �׸���
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

	// >> : hdc�� �׷��ֱ�
	TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void GameCenter::DeleteBitmap()
{
	tilemap.DeleteBitmap();
	player.DeleteBitmap();
	itemList.front()->DeleteBitmap();
	DeleteObject(hInvenImage);
}

void GameCenter::SaveTile()
{
	// ���� �о����
	wstring strFilePath = TEXT("tiles/test.tiles");
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile == nullptr)
	{
		MessageBox(NULL, TEXT("Ÿ�ϸ� ���� ����"), TEXT("����"), MB_OK);
		return;
	}

	// ������ ����
	UINT xCount = 16;
	UINT yCount = 16;

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	//CreateTiles(xCount, yCount);
	tilemap.DrawBitmapDoubleBuffering(m_hdc);

	fclose(pFile);
}

void GameCenter::LoadTile()
{
	// ���� �о����
	wstring strFilePath = TEXT("tiles/test.tiles");
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (pFile == nullptr)
	{
		MessageBox(NULL, TEXT("Ÿ�ϸ� ���� ����"), TEXT("����"), MB_OK);
		return;
	}

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// CreateTiles
	tilemap.DrawBitmapDoubleBuffering(m_hdc);


	fclose(pFile);
}