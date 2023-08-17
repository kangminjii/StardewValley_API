#pragma once
#include <Windows.h>

class Player;
class Item;

class CCollider
{
private:

	Player* pOwner;		// 콜라이더를 소유하는 오브젝트
	Item* iOwner;

	POINT finalPos;		// finalupdate에서 매 프레임마다 계산
	POINT scale;		// 충돌체의 크기

public:

	void setScale(POINT _scale) { scale = _scale; }
	POINT getScale() { return scale; }

public:

	CCollider();
	~CCollider();

	void FinalUpdate(HDC hdc);



	friend class Player;
	friend class Item;

};

