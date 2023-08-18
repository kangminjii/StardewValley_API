#include "Player.h"
#include "CCollider.h"
#include "Timer.h"

Player::Player()
    : position{ 100, 100 }, viewDir(NONE), speed(5), distance(0), p_Collider(nullptr), isCollided(FALSE), startRect{0,0}, endRect{0,0}
{
    CreateCollider();
}
Player::~Player()
{
    if (p_Collider != nullptr)
        delete p_Collider;
}

void Player::CreateCollider()
{
    p_Collider = new CCollider;
    p_Collider->pOwner = this;
}

void Player::Draw(HDC hdc, RECT rectView, HDC hMemDC, HBITMAP hOldBitmap, HDC hMemDC2, HBITMAP hOldBitmap2)
{
    // 주인공 이미지 & 애니메이션 들어갈부분
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
    hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, playerImage);
    int bx = bitPlayer.bmWidth; // 전체 너비
    int by = bitPlayer.bmHeight; // 전체 높이

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
    //timer 체크해야함
    //cout << "deltatime : " << playerTimer->getDeltaTime() << endl;
    //cout << "FPS : " << playerTimer->getFPS() << endl;

    // 초당 값의 변경을 일정하게 보장함
    //setDistance(10 * speed * getDeltaTime());
    //setDistance(getFPS() * speed * getDeltaTime());
    setDistance(3);

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if(!isCollided)
            setPosition({ getPositionX() - getDistance() , getPositionY() });

        viewDir = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (!isCollided)
            setPosition({ getPositionX() + getDistance() , getPositionY() });
        viewDir = RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (!isCollided)
            setPosition({ getPositionX(), getPositionY() - getDistance() });
        viewDir = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (!isCollided)
            setPosition({ getPositionX(), getPositionY() + getDistance() });
        viewDir = DOWN;
    }
    else
        viewDir = PAUSE;
}

void Player::UpdatePlayer(HDC hdc)
{
    // timer 클래스 사용
    //playerTimer->Update();       // getDeltaTime 고정
    //playerTimer->UpdateFPS();

   // if (p_Collider != nullptr)
    {
        setRect({ getPositionX() - 5, getPositionY() + 10, }, { getPositionX() + 30, getPositionY() + 70 });
        p_Collider->Paint(hdc);
    }
    
}

void Player::CollisionCheck()
{
    //cout << "iscollided : " << isCollided << endl;
    isCollided = p_Collider->isCollided;
}
