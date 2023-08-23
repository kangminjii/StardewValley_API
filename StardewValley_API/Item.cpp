#include "Item.h"


Item::Item()
	: position{0, 0}, startRect{0, 0}, endRect{0, 0}, mineCount(0)
{}

Item::~Item()
{}

Item::Item(POINT startLocation)
	: mineCount(0)
{
	position = startLocation;

	setRect({ getPositionX() - 4, getPositionY() }, { getPositionX() + 34, getPositionY() + 32 });
}
