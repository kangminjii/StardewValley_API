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

	POINT position;
    int viewDir;
    int speed;
    int distance;

    //Timer* playerTimer;

    POINT startRect;
    POINT endRect;

    bool isCollided;

public:

    // position 
    void setPosition(POINT pos) { position = pos; }
    int getPositionX() { return position.x; }
    int getPositionY() { return position.y; }

    // viewDir
    void setViewDir(int vd) { viewDir = vd; }
    int getViewDir() { return viewDir; }

    // speed
    void setDistance(int dis) { distance = dis; }
    int getDistance() { return distance; }

    // RECT - collision range
    void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
    POINT getStartRect() { return startRect; }
    POINT getEndRect() { return endRect; }

    // collided check
    void setCollided(bool check) { isCollided = check; }
    bool getCollided() { return isCollided; }


public:
	
    Player();
    ~Player();

    // func
	void Draw(HDC, RECT, HDC, HBITMAP, HDC, HBITMAP);
	void Move();
    void UpdatePlayer();

};

