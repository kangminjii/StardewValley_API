#pragma once
#include "Player.h"
#include "Item.h"
#include <list>

class GameCenter
{
private:

	Player player;
	std::list<Item*> itemList;
	
public:

	// player : �÷��̾� ��ü �ҷ�����
	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// item : �����۸���Ʈ ��ü �ҷ�����
	void setItemList() { addItem(); }
	std::list<Item*>& getItemList() { return itemList; }

public:

	GameCenter();
	~GameCenter();

	// ������ ����
	void addItem();
	void deleteItem();

	// >> : �ݺ������� üũ���ִ� �Լ�
	void Update();
	void OnCollision();
	void Render(HDC hdc);

	// �����ϴ��� üũ
	int isMining(HWND hWnd);

	// << :
};

