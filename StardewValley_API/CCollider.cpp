#include "CCollider.h"
#include "Player.h"
#include "Item.h"

CCollider::CCollider()
	: pOwner(nullptr), iOwner(nullptr), isCollided(FALSE), havepOwner(0), haveiOwner(0)
{
}
CCollider::~CCollider()
{
}

void CCollider::Paint(HDC hdc)
{
	if (pOwner != nullptr)
		cout << "pOwner 있음" << endl;
	else if(pOwner == nullptr)
		cout << "pOwner 없음" << endl;

	// 콜라이더의 owner 체크하기
	////////////////////////////// pOwner가 있다가 null돼버림
	if (pOwner)
	{
		havepOwner = 1;
		OnCollision();

		// x 30 y 65
		HBRUSH hBrush, oldBrush;
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		HPEN hPen, oldPen;
		hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		
		//cout << "Player " << endl;
		//cout << "startx, starty : " << pOwner->getStartRect().x << ", " << pOwner->getStartRect().y << endl;
		Rectangle(hdc, pOwner->getStartRect().x, pOwner->getStartRect().y, pOwner->getEndRect().x, pOwner->getEndRect().y);

		DeleteObject(hBrush);
		DeleteObject(hPen);
	}
	
	if (iOwner != nullptr)
		cout << "iOwner 있음" << endl;
	else if (iOwner == nullptr)
		cout << "iOwner 없음" << endl;

	if (iOwner)
	{
		haveiOwner = 1;
		OnCollision();

		// x 16 y 18
		HBRUSH hBrush, oldBrush;
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		HPEN hPen, oldPen;
		hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);

		//cout << "Item " << endl;
		//cout << "startx, starty : " << iOwner->getStartRect().x << ", " << iOwner->getStartRect().y << endl;
		Rectangle(hdc, iOwner->getStartRect().x, iOwner->getStartRect().y, iOwner->getEndRect().x, iOwner->getEndRect().y);


		DeleteObject(hBrush);
		DeleteObject(hPen);
	}
}

void CCollider::OnCollision()
{
	cout << "havepOwner" << havepOwner << endl;
	cout << "haveiOwner" << haveiOwner << endl;

	if (havepOwner == 1 && haveiOwner == 1)
	{
		if (pOwner->getStartRect().x + iOwner->getStartRect().x >= pOwner->getEndRect().x)
		{
			cout << "case1" << endl;
			if (pOwner->getStartRect().x <= pOwner->getEndRect().x + iOwner->getEndRect().x)
			{
				cout << "case2" << endl;

				if (pOwner->getStartRect().y + iOwner->getStartRect().y >= pOwner->getEndRect().y)
				{
					cout << "case3" << endl;

					if (pOwner->getStartRect().y <= pOwner->getEndRect().y + iOwner->getEndRect().y)
					{
						isCollided = true;
						cout << "collided! " << isCollided << endl;
					}
				}
			}
		}
		else
			cout << "범위설정?" << endl;
	}
	cout << "================collided fail " << isCollided << endl;
	isCollided = false;
}

