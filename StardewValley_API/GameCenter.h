#pragma once
#include "Player.h"
#include "Item.h"
#include <list>

class GameCenter
{
private:

	Player player;
	std::list<Item> itemList;

	
public:

	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// list
	void setItemList() { addItem(); }
	std::list<Item>& getItemList() { return itemList; }

	
public:

	GameCenter();
	~GameCenter();

	// ������ ����
	void addItem();
	void deleteItem();

	// �ݺ������� üũ���ִ� �Լ�
	void Update();

	void OnCollisionEnter();
	void OnCollision();
	void OnCollisionExit();

	void Render(HDC hdc);

};

