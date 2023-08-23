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

	// player : 플레이어 객체 불러오기
	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// item : 아이템리스트 객체 불러오기
	void setItemList() { addItem(); }
	std::list<Item*>& getItemList() { return itemList; }

public:

	GameCenter();
	~GameCenter();

	// 아이템 관리
	void addItem();
	void deleteItem();

	// >> : 반복적으로 체크해주는 함수
	void Update();
	void OnCollision();
	void Render(HDC hdc);

	// 광질하는지 체크
	int isMining(HWND hWnd);

	// << :
};

