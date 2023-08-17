#pragma once
#include <Windows.h>

class Player;
class Item;

class CCollider
{
private:

	Player* pOwner;		// �ݶ��̴��� �����ϴ� ������Ʈ
	Item* iOwner;

	POINT finalPos;		// finalupdate���� �� �����Ӹ��� ���
	POINT scale;		// �浹ü�� ũ��

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

