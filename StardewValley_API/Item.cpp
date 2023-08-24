#include "Define.h"
#include "Item.h"


Item::Item()
	: position{0, 0}, startRect{0, 0}, endRect{0, 0}, mineCount(0), paintType(EMPTY), hStoneImage(0)
{
	CreateBitmap();
}

Item::~Item()
{}

Item::Item(POINT startLocation, int pt)
	: mineCount(0)
{
	CreateBitmap();
	position = startLocation;
	paintType = pt;
	setRect({ getPositionX() - 4, getPositionY() }, { getPositionX() + 34, getPositionY() + 32 });
}

void Item::CreateBitmap()
{
	hStoneImage = (HBITMAP)LoadImage(NULL, TEXT("images/stones.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	if (hStoneImage == NULL) // 이미지가 출력되지 않을 때
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, TEXT("아이템 이미지 로드 에러"), TEXT("에러"), MB_OK);
		return;
	}

	GetObject(hStoneImage, sizeof(BITMAP), &bitStone);
}

void Item::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	
	// 돌 종류에 따라 다르게 paint
	if(this->paintType == stone1)
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStoneImage);
		bx = bitStone.bmWidth / 24;
		by = bitStone.bmHeight / 12;

		int xStart = bx * 8; // 가로에 있는 순서대로 출력이 됨
		int yStart = by;

		TransparentBlt(hdc, getPositionX(), getPositionY(), 31, 35, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	if(this->paintType == stone2)
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStoneImage);
		bx = bitStone.bmWidth / 24;
		by = bitStone.bmHeight / 12;

		int xStart = bx * 14; // 가로에 있는 순서대로 출력이 됨
		int yStart = by;

		TransparentBlt(hdc, getPositionX(),getPositionY(), 31, 35, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void Item::DeleteBitmap()
{
	DeleteObject(hStoneImage);
}