#pragma once
#include "Define.h"

enum itemType { stone1, stone2, stone3, EMPTY};

class Item
{
private:
	POINT position;

	POINT startRect;
	POINT endRect;

	int paintType; // 광물의 종류

public:
	// position : 아이템 위치
	void setPosition(POINT pos) { position = pos; }
	POINT getPosition() { return position; }

	// RECT : 아이템 collider 사각형
	void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
	POINT getStartRect() { return startRect; }
	POINT getEndRect() { return endRect; }

	// 광물의 종류 구분
	void setPaintType(int pt) { paintType = pt; }
	int getPaintType() { return paintType; }

public:
	Item();
	Item(POINT startLocation, int paintType);
	~Item();

//// 더블 버퍼링
private:
	HBITMAP hStoneImage;
	BITMAP  bitStone;

public:
	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HDC hdc);
	void DeleteBitmap();

};

