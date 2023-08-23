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

	// position : ������ ��ġ
	void setPosition(POINT pos) { position = pos; }
	int getPositionX() { return position.x; }
	int getPositionY() { return position.y; }

	// RECT : ������ collider �簢��
	void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
	POINT getStartRect() { return startRect; }
	POINT getEndRect() { return endRect; }

	// �������� ������ Ƚ�� ī��Ʈ
	void setMineCount(int mc) { mineCount = mc; }
	int getMineCount() { return mineCount; }

public:

	Item();
	Item(POINT startLocation);
	~Item();

};

