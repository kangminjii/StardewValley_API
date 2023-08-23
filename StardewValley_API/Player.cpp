#include "Player.h"
#include "Timer.h"

Player::Player()
    : position{ 100, 100 }, viewDir(NONE), preViewDir(NONE), speed(10), distance(0), startRect{0,0}, endRect{0,0}, 
    isCollidedL(false), isCollidedR(false), isCollidedU(false), isCollidedD(false),
    cursorPos{0, 0}
{
}
Player::~Player()
{
    
}

void Player::setCollided(bool check, int collidedView)
{
    if (collidedView == LEFT)
        isCollidedL = check;
    else if (collidedView == RIGHT)
        isCollidedR = check;
    else if (collidedView == UP)
        isCollidedU = check;
    else if (collidedView == DOWN)
        isCollidedD = check;
}



// 사용 안하는중
//void Player::Draw(HDC hdc, RECT rectView, HDC hMemDC, HBITMAP hOldBitmap, HDC hMemDC2, HBITMAP hOldBitmap2)
//{
//    // 주인공 이미지 & 애니메이션 들어갈부분
//   /* HDC hMemDC;
//    HBITMAP hOldBitmap;
//    HDC hMemDC2;
//    HBITMAP hOldBitmap2;*/
//    HBITMAP hDoubleBufferImage = NULL;
//
//    HBITMAP playerImage;
//    BITMAP bitPlayer;
//
//    hMemDC = CreateCompatibleDC(hdc);
//    if (hDoubleBufferImage == NULL)
//    {
//        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
//    }
//    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);
//
//    // create bitmap
//    playerImage = (HBITMAP)LoadImage(NULL, TEXT("images/player.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//    GetObject(playerImage, sizeof(BITMAP), &bitPlayer);
//
//    // double buffering
//    hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
//    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, playerImage);
//    int bx = bitPlayer.bmWidth; // 전체 너비
//    int by = bitPlayer.bmHeight; // 전체 높이
//
//    BitBlt(hMemDC, getPositionX(), getPositionY(), bx, by, hMemDC2, 0, 0, SRCCOPY);
//
//    SelectObject(hMemDC2, hOldBitmap2);
//    DeleteDC(hMemDC2);
//
//
//    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));
//
//    SelectObject(hMemDC, hOldBitmap);
//    DeleteDC(hMemDC);
//
//    // delete bitmap
//    DeleteObject(playerImage);
//
//    //Rectangle(hdc, getPositionX() - 20, getPositionY() - 20, getPositionX() + 20, getPositionY() + 20);
//}

void Player::Move()
{
    //timer 체크해야함
    //cout << "deltatime : " << playerTimer->getDeltaTime() << endl;
    //cout << "FPS : " << playerTimer->getFPS() << endl;

    // 초당 값의 변경을 일정하게 보장함
    //setDistance(10 * speed * getDeltaTime());
    //setDistance(getFPS() * speed * getDeltaTime());
    setDistance(3);

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        viewDir = LEFT;
        if (preViewDir != viewDir)  setCollided(false, preViewDir);

        if(!isCollidedL)
            setPosition({ getPosition().x - getDistance() , getPosition().y });
        else
        {
            if (viewDir == preViewDir)
                setPosition({ getPrevPosition().x , getPrevPosition().y });
        }

        preViewDir = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        viewDir = RIGHT;
        if (preViewDir != viewDir)  setCollided(false, preViewDir);

        if (!isCollidedR)
            setPosition({ getPosition().x + getDistance() , getPosition().y });
        else
        {
            if (viewDir == preViewDir)
                setPosition({ getPrevPosition().x , getPrevPosition().y });
        }

        preViewDir = RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        viewDir = UP;
        if (preViewDir != viewDir)  setCollided(false, preViewDir);

        if (!isCollidedU)
            setPosition({ getPosition().x, getPosition().y - getDistance() });
        else
        {
            if (viewDir == preViewDir)
                setPosition({ getPrevPosition().x , getPrevPosition().y });
        }

        preViewDir = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        viewDir = DOWN;
        if (preViewDir != viewDir)  setCollided(false, preViewDir);

        if (!isCollidedD)
            setPosition({ getPosition().x, getPosition().y + getDistance() });
        else
        {
            if (viewDir == preViewDir)
                setPosition({ getPrevPosition().x , getPrevPosition().y });
        }

       preViewDir = DOWN;
    }
    else
        viewDir = PAUSE;

}

void Player::Click(HWND hWnd)
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);
        cout << "mousePos : " << cursorPos.x << ", " << cursorPos.y << endl;
    }
    
    
    
    //if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
}

void Player::UpdatePlayer()
{
    // timer 클래스 사용
    //playerTimer->Update();       // getDeltaTime 고정
    //playerTimer->UpdateFPS();

    Move();
    setRect({ getPosition().x - 1, getPosition().y + 5, }, { getPosition().x + 43, getPosition().y + 80 });
}

