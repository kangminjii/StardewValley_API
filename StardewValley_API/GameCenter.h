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

	// 아이템 관리
	void addItem();
	void deleteItem();

	// 반복적으로 체크해주는 함수
	void Update();

	void OnCollisionEnter();
	void OnCollision();
	void OnCollisionExit();

	void Render(HDC hdc);

};

