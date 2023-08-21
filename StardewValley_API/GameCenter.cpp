#include "GameCenter.h"


// update -> render -> �浹 ó��
// object�� player, item ���� ,,, ���߿� �߰��Ҷ� index�� ���ͼ� �Ҽ��ְԲ�


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

	// ������ �߰��ϱ�

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


//OnCollisionEnter ��� �� �浹
//OnCollision �浹 ��
//OnCollisionExit �浹 ���


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

