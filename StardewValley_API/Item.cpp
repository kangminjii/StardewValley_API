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
	
	if (hStoneImage == NULL) // �̹����� ��µ��� ���� ��
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, TEXT("������ �̹��� �ε� ����"), TEXT("����"), MB_OK);
		return;
	}

	GetObject(hStoneImage, sizeof(BITMAP), &bitStone);
}

void Item::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
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

		int xStart = bx * 8; // ���ο� �ִ� ������� ����� ��
		int yStart = by;

		TransparentBlt(hdc, getPositionX(), getPositionY(), 31, 35, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	if(this->paintType == stone2)
	{
		hMemDC = CreateCompatibleDC(hdc); // ���� ����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hStoneImage);
		bx = bitStone.bmWidth / 24;
		by = bitStone.bmHeight / 12;

		int xStart = bx * 14; // ���ο� �ִ� ������� ����� ��
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