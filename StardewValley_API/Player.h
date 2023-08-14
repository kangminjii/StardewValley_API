#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "msimg32.lib")

static enum view { LEFT, RIGHT, UP, DOWN, PAUSE, NONE };
class Player
{
private:
	POINT position;
    int viewDir;

public:
	
    Player();

    // position 
    void setPosition(POINT pos) { position = pos; }
	int getPositionX() { return position.x; }
    int getPositionY() { return position.y; }

    // viewDir
    void setViewDir(int vd) { viewDir = vd; }
    int getViewDir() { return viewDir; }
	

	void Draw(HDC, RECT, HDC, HBITMAP, HDC, HBITMAP);
	void Move();

};

Player::Player()
{
    position = { 100, 100 };
    viewDir = NONE;
}

void Player::Draw(HDC hdc, RECT rectView, HDC hMemDC, HBITMAP hOldBitmap, HDC hMemDC2, HBITMAP hOldBitmap2)
{
    // ���ΰ� �̹��� & �ִϸ��̼� ���κ�
   /* HDC hMemDC;
    HBITMAP hOldBitmap;
    HDC hMemDC2;
    HBITMAP hOldBitmap2;*/
    HBITMAP hDoubleBufferImage = NULL;

    HBITMAP playerImage;
    BITMAP bitPlayer;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);
    
    // create bitmap
    playerImage = (HBITMAP)LoadImage(NULL, TEXT("images/player.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(playerImage, sizeof(BITMAP), &bitPlayer);

    // double buffering
    hMemDC2 = CreateCompatibleDC(hMemDC); // ���� ����
    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, playerImage);
    int bx = bitPlayer.bmWidth; // ��ü �ʺ�
    int by = bitPlayer.bmHeight; // ��ü ����

    BitBlt(hMemDC, getPositionX(), getPositionY(), bx, by, hMemDC2, 0, 0, SRCCOPY);

    SelectObject(hMemDC2, hOldBitmap2);
    DeleteDC(hMemDC2);

   
    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    // delete bitmap
    DeleteObject(playerImage);

    //Rectangle(hdc, getPositionX() - 20, getPositionY() - 20, getPositionX() + 20, getPositionY() + 20);
}

void Player::Move()
{
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        setPosition({ getPositionX() - 5 , getPositionY() });
        viewDir = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        setPosition({ getPositionX() + 5 , getPositionY() });
        viewDir = RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        setPosition({ getPositionX(), getPositionY() - 5 });
        viewDir = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        setPosition({ getPositionX(), getPositionY() + 5 });
        viewDir = DOWN;
    }
    else
        viewDir = PAUSE;
}
