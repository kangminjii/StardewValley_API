#include "Define.h"
#include "Tile.h"

Tile::Tile()
{
	CreateTile();
}

Tile::~Tile()
{
}

void Tile::CreateTile()
{
	// tilemap
	hTileImage = (HBITMAP)LoadImage(NULL, TEXT("images/mine_map.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hTileImage == NULL) // 이미지가 출력되지 않을 때
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, TEXT("타일맵 이미지 로드 에러"), TEXT("에러"), MB_OK);
		return;
	}

	GetObject(hTileImage, sizeof(BITMAP), &bitTile);

	// indexing
	//for (int i = 0; i < 16; i++)
	//{
	//	for (int j = 0; j < 16; j++)
	//	{
	//		Tile* tile = new Tile;
	//		tile->setIndex(i*16 + j);
	//		tile->setPosition({ j * 40, i * 40 }); // 크기 40x40
	//		tileList.push_back(tile);
	//	}
	//}

}
void Tile::DeleteTile()
{
	DeleteObject(hTileImage);
	DeleteObject(hBackImage);
}

void Tile::PaintTile(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc); 
	HBITMAP hTileBitmap, hBackBitmap;
	
	// background
	hBackBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
	BitBlt(hdc, 0, 0, 1000, 800, hMemDC, 0, 0, BLACKNESS);

	// tile
	hTileBitmap = (HBITMAP)SelectObject(hMemDC, hTileImage);

	// 256 pixel
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
			TransparentBlt(hdc, 200 + (40 * j), 50 + (40 * i), 40, 40, hMemDC, 16 * (map[i][j] % 16), 16 * (map[i][j] / 16), 16, 16, RGB(0, 0, 0));
	}

	SelectObject(hMemDC, hTileBitmap);
	DeleteDC(hMemDC);
}
