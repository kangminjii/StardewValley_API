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
    //// �̵� ����
    // position : �÷��̾� ��ġ
    void setPosition(Vec2 pos) { position = pos; }
    Vec2 getPosition() { return position; }
    void setPrevPosition(Vec2 prepos) { prevPosition = prepos; }
    Vec2 getPrevPosition() { return prevPosition; }

    // distance : �÷��̾� �̵��Ÿ�
    void setDistance(float dis) { distance = dis; }
    float getDistance() { return distance; }

    // viewDir : �÷��̾ ���� ����
    void setViewDir(int vd) { viewDir = vd; }
    int getpreViewDir() { return preViewDir; }
    int getViewDir() { return viewDir; }


    //// �浹 ����
    // RECT : �÷��̾� collider �簢��
    void setRect(POINT start, POINT end) { startRect = start; endRect = end; }
    POINT getStartRect() { return startRect; }
    POINT getEndRect() { return endRect; }

    // isCollided : �浹 üũ
    void setCollided(bool check, int collidedView);
    int getCollidedDir() { return preViewDir; }

    
    //// ��ȣ�ۿ� ����
    // cursor : ���콺 Ŀ�� ��ġ
    void setCursorPos(int x, int y) { cursorPos.x = x; cursorPos.y = y; }
    POINT getCursorPos() { return cursorPos; }

    // minecheck : ������ ������ Ÿ�̹��� ���� flag
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
    //// ���� ���۸�

    // �ִϸ��̼�
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

    // Ÿ�̸� �Լ�
    void UpdateFrame();
};

