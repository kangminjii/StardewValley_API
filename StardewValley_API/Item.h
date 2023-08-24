#pragma once
#include "Define.h"

enum itemType { stone1, stone2, EMPTY};


class Item
{
private:

	POINT position;

	POINT startRect;
	POINT endRect;

	int mineCount; // 없어질 클릭 횟수
	int paintType; // 광물의 종류

public:

	// position : 아이템 위치
	void setPosition(POINT pos) { position = pos; }
	int getPositionX() { return position.x; }
	int getPositionY() { return position.y; }

	// RECT : 아이템 collider 사각형
	void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
	POINT getStartRect() { return startRect; }
	POINT getEndRect() { return endRect; }

	// 아이템이 없어질 횟수 카운트
	void setMineCount(int mc) { mineCount = mc; }
	int getMineCount() { return mineCount; }

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

	int SPRITE_SIZE_X = 27; // x 길이 256
	int SPRITE_SIZE_Y = 60; // y 길이 256

	int RUN_FRAME_MAX = 0;
	int RUN_FRAME_MIN = 0;
	int curframe = RUN_FRAME_MIN;

public:
	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
	void DeleteBitmap();

};

