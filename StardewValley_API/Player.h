#pragma once
#include <iostream>
#include <Windows.h>
#include "Timer.h"

#pragma comment(lib, "msimg32.lib")

using namespace std;
enum view { LEFT, RIGHT, UP, DOWN, PAUSE, NONE };

class Player
{
private:

    //Timer* playerTimer;

	POINT position;
    POINT prevPosition;
    int distance;
    int speed;

    int viewDir;
    int preViewDir;

    POINT startRect;
    POINT endRect;

    bool isCollidedL;
    bool isCollidedR;
    bool isCollidedU;
    bool isCollidedD;

    POINT cursorPos;


public:

    // position : �÷��̾� ��ġ
    void setPosition(POINT pos) { position = pos; }
    POINT getPosition() { return position; }
    void setPrevPosition(POINT prepos) { prevPosition = prepos; }
    POINT getPrevPosition() { return prevPosition; }

    // distance : �÷��̾� �̵��Ÿ�
    void setDistance(int dis) { distance = dis; }
    int getDistance() { return distance; }


    // viewDir : �÷��̾ ���� ����
    void setViewDir(int vd) { viewDir = vd; }
    int getpreViewDir() { return preViewDir; }
    int getViewDir() { return viewDir; }

    // RECT : �÷��̾� collider �簢��
    void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
    POINT getStartRect() { return startRect; }
    POINT getEndRect() { return endRect; }

    // isCollided : �浹 üũ
    void setCollided(bool check, int collidedView);
    int getCollidedDir() { return preViewDir; }

    
    // cursor : ���콺 Ŀ�� ��ġ
    void setCursorPos(int x, int y) { cursorPos.x = x; cursorPos.y = y; }
    POINT getCursorPos() { return cursorPos; }

public:
	
    Player();
    ~Player();

    // func
	//void Draw(HDC, RECT, HDC, HBITMAP, HDC, HBITMAP);
	void Move();
    void Click(HWND hWnd);
    void UpdatePlayer();


};

