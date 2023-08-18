#pragma once
#include <Windows.h>

class Item;
class Player;

class CCollider
{
private:

	Player* pOwner;		// 콜라이더를 소유하는 오브젝트
	Item* iOwner;

	BOOL isCollided;	// 충돌체크

	// 체크용 플래그
	int havepOwner;
	int haveiOwner;

public:

	//void setHaveiOwner(int i) { haveiOwner = i; }

public:

	CCollider();
	~CCollider();

	void Paint(HDC hdc);
	void OnCollision();

	// private 멤버에 접근하기 위한 friend 선언
	friend class Player;
	friend class Item;

};

