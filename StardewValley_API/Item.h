#pragma once
#include <Windows.h>

class Item
{
private:

	POINT position;

	POINT startRect;
	POINT endRect;

	int mineCount;

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

public:

	Item();
	Item(POINT startLocation);
	~Item();

};

