#pragma once
#include "Define.h"

enum itemType { stone1, stone2, EMPTY};


class Item
{
private:

	POINT position;

	POINT startRect;
	POINT endRect;

	int mineCount; // ������ Ŭ�� Ƚ��
	int paintType; // ������ ����

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

	int SPRITE_SIZE_X = 27; // x ���� 256
	int SPRITE_SIZE_Y = 60; // y ���� 256

	int RUN_FRAME_MAX = 0;
	int RUN_FRAME_MIN = 0;
	int curframe = RUN_FRAME_MIN;

public:
	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
	void DeleteBitmap();

};

