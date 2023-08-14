#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class Item
{
private:

	POINT position;

public:

	Item();

	// position
	void setPosition(POINT pos) { position = pos; }
	int getPositionX() { return position.x; }
	int getPositionY() { return position.y; }


};

Item::Item()
{
	position = { 0, 0 };
}
