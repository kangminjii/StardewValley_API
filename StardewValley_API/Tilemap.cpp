#include "Define.h"
#include "Tilemap.h"

Tilemap::Tilemap()
	: tiles(ROW, vector<POINT>(COL)), position{ 0,0 }, hMapImage(0), hBackImage(0)
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
	// tilemap
	{
		hMapImage = (HBITMAP)LoadImage(NULL, TEXT("images/mine_map.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hMapImage == NULL) // 이미지가 출력되지 않을 때
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, TEXT("타일맵 이미지 로드 에러"), TEXT("에러"), MB_OK);
			return;
		}

		GetObject(hMapImage, sizeof(BITMAP), &bitMap);
	}
	
	// black background
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hBackImage == NULL) // 이미지가 출력되지 않을 때
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, TEXT("맵 백그라운드 이미지 로드 에러"), TEXT("에러"), MB_OK);
			return;
		}

		GetObject(hMapImage, sizeof(BITMAP), &bitBack);
	}
}

void Tilemap::DrawBitmapDoubleBuffering(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hTileBitmap, hBackBitmap;
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
		{by*15,by*4,by*4,by*4,by*4,by*4,by*4,by*4,		by*4,by*4,by*4,by*4,by*4,by*4,by*4,by*4},
		{by*15,by*4,by*4,by*4,by*5,by*4,by*4,by*4,		by*4,by*5,by*4,by*4,by*4,by*4,by*4,by*4},
		{by*15,by*5,by*5,by*5,by*6,by*5,by*5,by*5,		by*5,by*6,by*6,by*6,by*6,by*6,by*4,by*4},
		{by*15,by*6,by*6,by*6,by*7,by*7,by*7,by*6,		by*6,by*7,by*7,by*7,by*7,by*7,by*4,by*4},
		{by*15,by*7,by*7,by*7,by*8,by*8,by*8,by*7,		by*7,by*8,by*8,by*8,by*8,by*8,by*4,by*4},
		{by*15,by*8,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*9,by*4,by*4},
		{by*15,by*8,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*9,by*4,by*4},
		{by*15,by*12,by*8,by*8,by*8,by*8,by*8,by*8,		by*8,by*8,by*8,by*8,by*8,by*8,by*4,by*4},
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
		
		// background
		hBackBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
		BitBlt(hdc, 0, 0, 1000, 800, hMemDC, 0, 0, BLACKNESS);

		// tile
		hTileBitmap = (HBITMAP)SelectObject(hMemDC, hMapImage);

		// 256 pixel
		for (int i = 3; i < 18; i++)
		{
			for (int j = 5; j < 20; j++)
				TransparentBlt(hdc, tiles[i][j].x, tiles[i][j].y, 40, 40, hMemDC, xStart[i - 3][j - 5], yStart[i - 3][j - 5], bx, by, RGB(0, 0, 0));
		}
		
		SelectObject(hMemDC, hTileBitmap);
		DeleteDC(hMemDC);
	}
}

void Tilemap::DeleteBitmap()
{
	DeleteObject(hMapImage);
	DeleteObject(hBackImage);
}

void Tilemap::SaveTile()
{
	// 파일 읽어오기
	wstring strFilePath = TEXT("tiles/test.tiles");
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile == nullptr)
	{
		MessageBox(NULL, TEXT("타일맵 저장 에러"), TEXT("에러"), MB_OK);
		return;
	}

	// 데이터 저장
	UINT xCount = 16;
	UINT yCount = 16;

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	//CreateTiles


	fclose(pFile);
}

void Tilemap::LoadTile()
{
	// 파일 읽어오기
	wstring strFilePath = TEXT("tiles/test.tiles");
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile == nullptr)
	{
		MessageBox(NULL, TEXT("타일맵 저장 에러"), TEXT("에러"), MB_OK);
		return;
	}

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	//CreateTile(xCount, yCount);



	fclose(pFile);
}
