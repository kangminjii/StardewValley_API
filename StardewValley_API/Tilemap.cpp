#include "Define.h"
#include "Tilemap.h"

Tilemap::Tilemap()
	: tiles(ROW, vector<POINT>(COL)), position{ 0,0 }, hMapImage(0)
{
	setTiles();
	CreateBitmap();
}

Tilemap::~Tilemap()
{
}

void Tilemap::setTiles()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			tiles[i][j] = { 40 * j, 40 * i };
		}
	}
}

void Tilemap::CreateBitmap()
{
	hMapImage = (HBITMAP)LoadImage(NULL, TEXT("images/mine_map.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hMapImage == NULL) // 이미지가 출력되지 않을 때
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, TEXT("맵 이미지 로드 에러"), TEXT("에러"), MB_OK);
		return;
	}

	GetObject(hMapImage, sizeof(BITMAP), &bitMap);
}

void Tilemap::DrawBitmapDoubleBuffering(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx = bitMap.bmWidth / 16;
	int by = bitMap.bmHeight / 16;
	vector<vector<int>> xStart(ROW, vector<int>(COL)), yStart(ROW, vector<int>(COL));
	xStart =
	{
		// top left  /  top right
		{bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,	bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*15,bx*15,bx*15,bx*5,bx*1,bx*2,bx*3,		bx*12,bx*13,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*5,bx*6,bx*7,bx*5,bx*1,bx*2,bx*3,			bx*12,bx*13,bx*14,bx*14,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*5,bx*6,bx*7,bx*5,bx*6,bx*7,bx*3,			bx*12,bx*13,bx*14,bx*14,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*5,bx*6,bx*7,bx*5,bx*6,bx*7,bx*3,			bx*12,bx*13,bx*14,bx*14,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*5,bx*6,bx*7,bx*9,bx*9,bx*9,bx*9,			bx*9,bx*13,bx*14,bx*14,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*14,bx*15,bx*15},
		{bx*15,bx*5,bx*10,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*15,bx*15},
		// bottom left  /  bottom right
		{bx*15,bx*15,bx*4,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*13,bx*15},
		{bx*15,bx*15,bx*4,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*13,bx*15},
		{bx*15,bx*15,bx*4,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*13,bx*15},
		{bx*15,bx*15,bx*4,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*13,bx*15},
		{bx*15,bx*15,bx*4,bx*9,bx*10,bx*9,bx*10,bx*9,		bx*9,bx*10,bx*9,bx*10,bx*9,bx*10,bx*13,bx*15},
		{bx*15,bx*15,bx*4,bx*6,bx*7,bx*9,bx*10,bx*9,		bx*6,bx*7,bx*9,bx*10,bx*9,bx*10,bx*15,bx*15},
		{bx*15,bx*15,bx*4,bx*15,bx*15,bx*9,bx*10,bx*9,		bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15},
		{bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,   bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15,bx*15},
	};
	yStart =
	{
		// top left   /   top right
		{by*4,by*4,by*4,by*4,by*4,by*4,by*4,by*4,		by*4,by*4,by*4,by*4,by*4,by*4,by*4,by*4},
		{by*4,by*4,by*4,by*4,by*5,by*4,by*4,by*4,		by*4,by*5,by*4,by*4,by*4,by*4,by*4,by*4},
		{by*4,by*5,by*5,by*5,by*6,by*5,by*5,by*5,		by*5,by*6,by*6,by*6,by*6,by*6,by*4,by*4},
		{by*4,by*6,by*6,by*6,by*7,by*7,by*7,by*6,		by*6,by*7,by*7,by*7,by*7,by*7,by*4,by*4},
		{by*4,by*7,by*7,by*7,by*8,by*8,by*8,by*7,		by*7,by*8,by*8,by*8,by*8,by*8,by*4,by*4},
		{by*4,by*8,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*9,by*4,by*4},
		{by*4,by*8,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*9,by*4,by*4},
		{by*4,by*12,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*4,by*4},
		// bottom left  /  bottom right
		{by*4,by*4,by*4,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*5,by*4},
		{by*4,by*4,by*5,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*6,by*4},
		{by*4,by*4,by*6,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*7,by*4},
		{by*4,by*4,by*7,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*8,by*4},
		{by*4,by*4,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*9,by*4},
		{by*4,by*4,by*9,by*13,by*13,by*8,by*8,by*8,		by*13,by*13,by*8,by*8,by*8,by*8,by*4,by*4},
		{by*4,by*4,by*10,by*4,by*4,by*8,by*8,by*8,		by*4,by*4,by*4,by*4,by*4,by*4,by*4,by*4},
		{by*4,by*4,by*4,by*4,by*4,by*4,by*4,by*4,		by*4,by*4,by*4,by*4,by*4,by*4,by*4,by*4},
	};

	// 광산 Map
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hMapImage);
		
		// 256 pixel
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
				TransparentBlt(hdc, tiles[i][j].x + 150, tiles[i][j].y + 100, 40, 40, hMemDC, xStart[i][j], yStart[i][j], bx, by, RGB(0, 0, 0));
		}
		
		// 빈곳이 있는 부분은 아래에 바닥을 먼저 설치하고 그리기


		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void Tilemap::DeleteBitmap()
{
	DeleteObject(hMapImage);
}
