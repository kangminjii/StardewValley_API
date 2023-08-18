#pragma once
#include <Windows.h>

class CCollider;

class Item
{
private:
	POINT position;

	CCollider* it_Collider;

	POINT startRect;
	POINT endRect;

public:

	// position
	void setPosition(POINT pos) { position = pos; }
	int getPositionX() { return position.x; }
	int getPositionY() { return position.y; }

	// RECT
	void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
	POINT getStartRect() { return startRect; }
	POINT getEndRect() { return endRect; }

public:

	Item();
	~Item();

	void CreateCollider();
	void UpdateItem(HDC hdc);
};

