#include "CCollider.h"
#include "Player.h"
#include "Item.h"

CCollider::CCollider()
	: pOwner(nullptr), iOwner(nullptr), finalPos{ 0,0 }, scale{ 0,0 }
{
}
CCollider::~CCollider()
{

}

void CCollider::FinalUpdate(HDC hdc)
{
	// 충돌 체크할 사각형 범위 좌표
	int collidedRange[4] = {0};

	// 콜라이더의 owner 체크하기
	if (pOwner)
	{
		// x 30 y 65
		finalPos = { pOwner->getPositionX(),pOwner->getPositionY() };
		
		collidedRange[0] = finalPos.x - 5;
		collidedRange[1] = finalPos.x + 30;
		collidedRange[2] = finalPos.y + 10;
		collidedRange[3] = finalPos.y + 70;
	}
	else if (iOwner)
	{
		// x 16 y 18
		finalPos = { iOwner->getPositionX(),iOwner->getPositionY() };

		collidedRange[0] = finalPos.x - 8;
		collidedRange[1] = finalPos.x + 8;
		collidedRange[2] = finalPos.y - 9;
		collidedRange[3] = finalPos.y + 9;
	}

	HBRUSH hBrush, oldBrush;
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	HPEN hPen, oldPen;
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc, collidedRange[0], collidedRange[2], collidedRange[1], collidedRange[3]);

	DeleteObject(hBrush);
	DeleteObject(hPen);
	
}

