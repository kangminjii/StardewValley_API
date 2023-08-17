#pragma once
#include <Windows.h>
#include "CCollider.h"

using namespace std;

class Item
{
private:
	POINT position;

	CCollider* it_Collider;

public:

	// position
	void setPosition(POINT pos) { position = pos; }
	int getPositionX() { return position.x; }
	int getPositionY() { return position.y; }

public:

	Item();
	~Item();




};

Item::Item()
	: position{0,0}, it_Collider(nullptr)
{
}
Item::~Item()
{
	if (it_Collider != nullptr)
		delete it_Collider;
}

