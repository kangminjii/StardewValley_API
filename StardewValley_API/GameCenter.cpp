#include "GameCenter.h"


// update -> render -> 충돌 처리
// object로 player, item 관리 ,,, 나중에 추가할때 index만 따와서 할수있게끔


GameCenter::GameCenter()
{
	setPlayer(player);
	addItem();
	//setItemList();
	if (itemList.empty())	cout << "list is empty" << endl;
}

GameCenter::~GameCenter()
{
}

void GameCenter::Update()
{
	player.UpdatePlayer();

	// 렌더링 추가하기

	OnCollision();
}

void GameCenter::addItem()
{
	Item i1({200, 200});
	itemList.push_back(&i1);

	Item i2({ 300, 300 });
	itemList.push_back(&i2);
}

void GameCenter::deleteItem()
{
}

void GameCenter::Render(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	HPEN hPen, oldPen;
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc, player.getStartRect().x, player.getStartRect().y, player.getEndRect().x, player.getEndRect().y);
	for (auto it = itemList.begin(); it != itemList.end(); it++)
		Rectangle(hdc, (*it)->getStartRect().x, (*it)->getStartRect().y, (*it)->getEndRect().x, (*it)->getEndRect().y);


	DeleteObject(hBrush);
	DeleteObject(hPen);
}


//OnCollisionEnter 방금 막 충돌
//OnCollision 충돌 중
//OnCollisionExit 충돌 벗어남


void GameCenter::OnCollision()
{
	for (auto it = itemList.begin(); it != itemList.end(); it++)
	{
		if (player.getStartRect().x + 3 < (*it)->getEndRect().x && (*it)->getStartRect().x + 3 < player.getEndRect().x)
		{
			if (player.getStartRect().y + 3 < (*it)->getEndRect().y && player.getEndRect().y + 3 > (*it)->getStartRect().y)
			{
				player.setCollided(true);
				cout << "collided! " << player.getCollided() << endl;
				cout << "player rect:" << player.getStartRect().x << ", " << player.getStartRect().y << endl;
			}
		}
	}
	
}

void GameCenter::OnCollisionEnter()
{

}

void GameCenter::OnCollisionExit()
{

}

