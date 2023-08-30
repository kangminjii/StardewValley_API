#pragma once
#include "Define.h"

enum itemType { stone1, stone2, stone3, EMPTY};

class Item
{
private:
	POINT position;

	POINT startRect;
	POINT endRect;
	RECT rectI;

	int paintType; // ������ ����

public:
	// position : ������ ��ġ
	void setPosition(POINT pos) { position = pos; }
	POINT getPosition() { return position; }

	// RECT : ������ collider �簢��
	void setRect(POINT start, POINT end) { startRect = start; endRect = end; rectI = { start.x, start.y, end.x, end.y }; }
	POINT getStartRect() { return startRect; }
	POINT getEndRect() { return endRect; }
	LPRECT getRect() { return &rectI; }
	

	// ������ ���� ����
	void setPaintType(int pt) { paintType = pt; }
	int getPaintType() { return paintType; }

public:
	Item();
	Item(POINT startLocation, int paintType);
	~Item();

//// ���� ���۸�
private:
	HBITMAP hStoneImage;
	BITMAP  bitStone;

public:
	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HDC hdc);
	void DeleteBitmap();

};

