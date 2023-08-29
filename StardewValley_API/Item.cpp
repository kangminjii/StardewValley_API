#include "Define.h"
#include "Item.h"


Item::Item()
	: position{0, 0}, startRect{0, 0}, endRect{0, 0}, paintType(EMPTY), hStoneImage(0)
{
	CreateBitmap();
}

Item::~Item()
{}

Item::Item(POINT startLocation, int pt)
{
	CreateBitmap();
	position = startLocation;
	paintType = pt;
	setRect({ getPosition().x - 4, getPosition().y }, { getPosition().x + 34, getPosition().y + 32 });
}

void Item::CreateBitmap()
{
	hStoneImage = (HBITMAP)LoadImage(NULL, TEXT("images/stones.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	if (hStoneImage == NULL) // �̹����� ��µ��� ���� ��
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, TEXT("������ �̹��� �ε� ����"), TEXT("����"), MB_OK);
		return;
	}

	GetObject(hStoneImage, sizeof(BITMAP), &bitStone);
}

void Item::DrawBitmapDoubleBuffering(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	
	// �� ������ ���� �ٸ��� paint
	if(this->paintType == stone1)
	{
		hMemDC = CreateCompatibleDC(hdc); // ���� ����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStoneImage);
		bx = bitStone.bmWidth / 24;
		by = bitStone.bmHeight / 12;

		int xStart = bx * 4; // ���ο� �ִ� ������� ����� ��
		int yStart = by;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 31, 35, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	else if(this->paintType == stone2)
	{
		hMemDC = CreateCompatibleDC(hdc); 
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStoneImage);
		bx = bitStone.bmWidth / 24;
		by = bitStone.bmHeight / 12 - 1;

		int xStart = bx * 6; 
		int yStart = by;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 31, 35, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	else if (this->paintType == stone3)
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStoneImage);
		bx = bitStone.bmWidth / 24;
		by = bitStone.bmHeight / 12;

		int xStart = bx * 8;
		int yStart = by;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 31, 35, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void Item::DeleteBitmap()
{
	DeleteObject(hStoneImage);
}