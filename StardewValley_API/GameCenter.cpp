#include "GameCenter.h"
#include <cmath>
#include <cstdlib>

// update -> render -> 충돌 처리
// object로 player, item 관리 ,,, 나중에 추가할때 index만 따와서 할수있게끔


GameCenter::GameCenter()
{
	setPlayer(player);
	addItem();
}

GameCenter::~GameCenter()
{
}

void GameCenter::Update()
{
	player.UpdatePlayer();

	// 렌더링 추가하기

	OnCollision();
	//isMining(hWnd);
}

int GameCenter::isMining(HWND hWnd)
{
	player.Click(hWnd);

	//if (abs(player.getPosition().x - player.getCursorPos().x) <= 50 && abs(player.getPosition().y - player.getCursorPos().y) <= 50)
	{
		//cout << "near" << endl;
		for (auto it = itemList.begin(); it != itemList.end(); it++)
		{
			if ((*it)->getPositionX() - 4 <= player.getCursorPos().x && player.getCursorPos().x <= (*it)->getPositionX() + 34)
			{
				if ((*it)->getPositionY() <= player.getCursorPos().y && player.getCursorPos().y <= (*it)->getPositionY() + 32)
				{
					// 아이템 삭제
					if ((*it)->getMineCount() == 2)
					{
						(*it)->setMineCount(0);
						delete (*it);
						return 3;
					}
					else if ((*it)->getMineCount() == 0)
					{
						(*it)->setMineCount(1);
						return 1;
					}
					else if ((*it)->getMineCount() == 1)
					{
						(*it)->setMineCount(2);
						return 2;
					}
				}
			}
		}
	}

	return 0;
	
}

void GameCenter::addItem()
{
	// 랜덤으로 줄시 겹치는 경우 발생
	srand(time(NULL));
	Item* i1 = new Item({ (rand() % 2) + 200, (rand() % 2) + 200 }); // 200,300
	itemList.push_back(i1);

	Item* i2 = new Item({ 250, 250});
	itemList.push_back(i2);

	Item* i3 = new Item({ 350, 350});
	itemList.push_back(i3);

	Item* i4 = new Item({ 400, 400 });
	itemList.push_back(i4);
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


void GameCenter::OnCollision()
{
	for (auto it = itemList.begin(); it != itemList.end(); it++)
	{
		// x축
		if (player.getStartRect().x + 2 < (*it)->getEndRect().x && (*it)->getStartRect().x < player.getEndRect().x + 2)
		{
			if (player.getStartRect().y + 2  < (*it)->getEndRect().y && player.getEndRect().y + 2 > (*it)->getStartRect().y )
			{
				cout << "collided! " << player.getCollidedDir() << endl;
				player.setCollided(true, player.getViewDir());
				player.setPrevPosition(player.getPosition());
			}
			else
			{
				player.setCollided(false, player.getpreViewDir());
			}
		}
		// y축
		if (player.getStartRect().y + 2 < (*it)->getEndRect().y && player.getEndRect().y + 2 > (*it)->getStartRect().y)
		{
			if (player.getStartRect().x + 2 < (*it)->getEndRect().x && (*it)->getStartRect().x < player.getEndRect().x + 2)
			{
				cout << "collided! " << player.getCollidedDir() << endl;
				player.setCollided(true, player.getViewDir());
				player.setPrevPosition(player.getPosition());
			}
			else
			{
				player.setCollided(false, player.getpreViewDir());
			}
		}
	}
	
}
