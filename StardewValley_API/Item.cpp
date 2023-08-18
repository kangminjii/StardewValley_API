#include "Item.h"
#include "CCollider.h"


Item::Item()
	: position{ 0,0 }, it_Collider(nullptr), startRect{0,0}, endRect{0,0}
{
	CreateCollider();
}
Item::~Item()
{
	if (it_Collider != nullptr)
		delete it_Collider;
}

void Item::CreateCollider()
{
	it_Collider = new CCollider;
	it_Collider->iOwner = this;
}

void Item::UpdateItem(HDC hdc)
{
	if (it_Collider)
	{
		setRect({ getPositionX() + 1, getPositionY() - 4 }, { getPositionX() + 17, getPositionY() + 14 });
		it_Collider->Paint(hdc);
	}
}