#pragma once
#include "Define.h"
#include "Timer.h"
#pragma comment(lib, "msimg32.lib")

using namespace std;
enum view { LEFT, RIGHT, UP, DOWN, PAUSE, NONE };

class Player
{
private:
    Timer* playerTimer;

	Vec2 position;
    Vec2 prevPosition;
    float distance;
    float speed;

    int viewDir;
    int preViewDir;

    POINT startRect;
    POINT endRect;

    bool isCollidedL;
    bool isCollidedR;
    bool isCollidedU;
    bool isCollidedD;

    POINT cursorPos;
    bool mineTimeChecked;
    bool isMining;
    int miningCycle = 0;

public:
    //// 이동 관련
    // position : 플레이어 위치
    void setPosition(Vec2 pos) { position = pos; }
    Vec2 getPosition() { return position; }
    void setPrevPosition(Vec2 prepos) { prevPosition = prepos; }
    Vec2 getPrevPosition() { return prevPosition; }

    // distance : 플레이어 이동거리
    void setDistance(float dis) { distance = dis; }
    float getDistance() { return distance; }

    // viewDir : 플레이어가 보는 방향
    void setViewDir(int vd) { viewDir = vd; }
    int getpreViewDir() { return preViewDir; }
    int getViewDir() { return viewDir; }


    //// 충돌 관련
    // RECT : 플레이어 collider 사각형
    void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
    POINT getStartRect() { return startRect; }
    POINT getEndRect() { return endRect; }

    // isCollided : 충돌 체크
    void setCollided(bool check, int collidedView);
    int getCollidedDir() { return preViewDir; }

    
    //// 상호작용 관련
    // cursor : 마우스 커서 위치
    void setCursorPos(int x, int y) { cursorPos.x = x; cursorPos.y = y; }
    POINT getCursorPos() { return cursorPos; }

    // minecheck : 광석이 없어질 타이밍을 위한 flag
    void setMineCheck(bool mine) { mineTimeChecked = mine; }
    bool getMineCheck() { return mineTimeChecked; }



public:
    Player();
    ~Player();

    // func
	void Move();
    void Click(HWND hWnd);
    void UpdatePlayer();


private:
    //// 더블 버퍼링

    // 애니메이션
    HBITMAP hAniImage;
    BITMAP bitAni;
    HBITMAP hAniLeftImage;
    BITMAP bitAniLeft;

    HBITMAP hShirtImage;
    BITMAP bitShirt;

    HBITMAP hHairImage;
    BITMAP bitHair;
    HBITMAP hHairLeftImage;
    BITMAP bitHairLeft;

    int curframe = 0;
    int curframeMine = 0;
    float timePerSecond = 0;

    HBITMAP hToolImage;
    BITMAP bitTool;

public:
    void CreateBitmap();
    void DrawBitmapDoubleBuffering(HDC hdc);
    void DeleteBitmap();

    // 타이머 함수
    void UpdateFrame();
};

