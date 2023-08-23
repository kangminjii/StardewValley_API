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

    // position : 플레이어 위치
    void setPosition(POINT pos) { position = pos; }
    POINT getPosition() { return position; }
    void setPrevPosition(POINT prepos) { prevPosition = prepos; }
    POINT getPrevPosition() { return prevPosition; }

    // distance : 플레이어 이동거리
    void setDistance(int dis) { distance = dis; }
    int getDistance() { return distance; }


    // viewDir : 플레이어가 보는 방향
    void setViewDir(int vd) { viewDir = vd; }
    int getpreViewDir() { return preViewDir; }
    int getViewDir() { return viewDir; }

    // RECT : 플레이어 collider 사각형
    void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
    POINT getStartRect() { return startRect; }
    POINT getEndRect() { return endRect; }

    // isCollided : 충돌 체크
    void setCollided(bool check, int collidedView);
    int getCollidedDir() { return preViewDir; }

    
    // cursor : 마우스 커서 위치
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

