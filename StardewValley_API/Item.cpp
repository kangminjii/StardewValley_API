#include "Item.h"


Item::Item()
	: position{0, 0}, startRect{0, 0}, endRect{0, 0}
{
	
}
Item::~Item()
{
}
Item::Item(POINT startLocation)
{
	position = startLocation;

	setRect({ getPositionX() - 10, getPositionY() - 10 }, { getPositionX() + 30, getPositionY() + 30 });
	//setRect({ getPositionX() + 1, getPositionY() - 4 }, { getPositionX() + 17, getPositionY() + 14 });
}
