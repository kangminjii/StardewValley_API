#pragma once
#include <iostream>
#include <Windows.h>

#pragma comment(lib, "msimg32.lib")

using namespace std;
enum view { LEFT, RIGHT, UP, DOWN, PAUSE, NONE };

class CCollider;
class Timer;

class Player
{
private:
	POINT position;
    int viewDir;
    int speed;
    int distance;

    Timer* playerTimer;
    CCollider* p_Collider;

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

public:
	
    Player();
    ~Player();

    // func
	void Draw(HDC, RECT, HDC, HBITMAP, HDC, HBITMAP);
	void Move();
    void UpdatePlayer(HDC hdc);

    // collider
    void CreateCollider();

};

