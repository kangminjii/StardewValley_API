#pragma once
#include <Windows.h>

class Item;
class Player;

class CCollider
{
private:

	Player* pOwner;		// �ݶ��̴��� �����ϴ� ������Ʈ
	Item* iOwner;

	BOOL isCollided;	// �浹üũ

	// üũ�� �÷���
	int havepOwner;
	int haveiOwner;

public:

	//void setHaveiOwner(int i) { haveiOwner = i; }

public:

	CCollider();
	~CCollider();

	void Paint(HDC hdc);
	void OnCollision();

	// private ����� �����ϱ� ���� friend ����
	friend class Player;
	friend class Item;

};

