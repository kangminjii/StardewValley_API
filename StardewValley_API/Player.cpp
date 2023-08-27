#include "Define.h"
#include "Player.h"

Player::Player()
    : position{ 300, 100}, prevPosition{ 0, 0 }, viewDir(NONE), preViewDir(NONE), speed(200.f), distance(0), startRect{ 0,0 }, endRect{ 0,0 },
    isCollidedL(false), isCollidedR(false), isCollidedU(false), isCollidedD(false), cursorPos{ 0, 0 },
    hAniImage(0), hShirtImage(0), hHairImage(0)
{
    CreateBitmap();
    playerTimer = new Timer;
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

void Player::CreateBitmap()
{
    // player animation
    {
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/player.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("애니메이션1 이미지 로드 에러"), TEXT("에러"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        RUN_FRAME_MAX = bitAni.bmWidth / 96 - 2;
        RUN_FRAME_MIN = 0;
        curframe = RUN_FRAME_MIN; // 0~2 frame
    }

    // shirts
    {
        hShirtImage = (HBITMAP)LoadImage(NULL, TEXT("images/shirts.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hShirtImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("애니메이션2 이미지 로드 에러"), TEXT("에러"), MB_OK);
            return;
        }

        GetObject(hShirtImage, sizeof(BITMAP), &bitShirt);
    }

    // hairs
    {
        hHairImage = (HBITMAP)LoadImage(NULL, TEXT("images/hair.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hHairImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("애니메이션3 이미지 로드 에러"), TEXT("에러"), MB_OK);
            return;
        }

        GetObject(hHairImage, sizeof(BITMAP), &bitHair);
    }
}

void Player::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    hMemDC = CreateCompatibleDC(hdc);

    HBITMAP hAniBitmap, hShirtBitmap, hHairBitmap;

    // AniImage 변수
    int bx1 = bitAni.bmWidth / 23;
    int by1 = bitAni.bmHeight / 20;

    // 상의 변수
    int bx2 = bitShirt.bmWidth / 15;
    int by2 = bitShirt.bmHeight / 27;

    // 머리 변수
    int bx3 = bitHair.bmWidth / 8; 
    int by3 = bitHair.bmHeight / 12; 

    //down
    if (getViewDir() == DOWN)
    {
        // 몸-바지
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = curframe * bx1;           // 몸
        int xStart2 = (curframe + 18) * bx1;    // 바지
        int yStart1 = by1 * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // 상의
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2로 상의 변경 가능
        int yStart3 = 0;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // 팔
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 6) * bx1;      // 팔

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // 머리
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 6;

        TransparentBlt(hdc, getPosition().x, getPosition().y -15, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
    }
	// left
    else if (getViewDir() == LEFT)
	{
        ///// 좌우반전필요
        // 몸-바지
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = (curframe + 2)* bx1;     // 몸
        int xStart2 = (curframe + 20) * bx1; // 바지
        int yStart1 = by1 * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // 상의
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2로 상의 변경 가능
        int yStart3 = 0;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // 팔
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 8) * bx1; // 팔

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // 머리
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 7;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 22, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
	}
	// up
	else if (getViewDir() == UP)
	{
        // 몸-바지
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = (curframe + 4) * bx1;     // 몸
        int xStart2 = (curframe + 22) * bx1;    // 바지
        int yStart1 = by1 * 3 - 1;

        cout << "xStart2 : " << xStart2 << " / bx1 : " << bx1 << endl;
        if (xStart2+bx1 >= bitAni.bmWidth)    xStart2 = bitAni.bmWidth - 16;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // 상의
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2로 상의 변경 가능
        int yStart3 = by2 *3;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 36, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // 팔
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 10) * bx1; // 팔
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // 머리
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 8;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 22, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
	}
	// right
	else if (getViewDir() == RIGHT)
	{
        // 몸-바지
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = (curframe + 2) * bx1;     // 몸
        int xStart2 = (curframe + 20) * bx1; // 바지
        int yStart1 = by1 * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // 상의
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2로 상의 변경 가능
        int yStart3 = 0;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // 팔
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 8) * bx1; // 팔

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // 머리
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 7;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 22, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
	}
    else if (getViewDir() == PAUSE)
    {
        // 몸-바지
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = 0;           // 몸
        int xStart2 = 18 * bx1;    // 바지
        int yStart1 = 0;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // 상의
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2로 상의 변경 가능
        int yStart3 = 0;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // 팔
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = 6 * bx1;   // 팔

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // 머리
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 6;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 15, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
        }
}
void Player::DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hShirtImage);
    DeleteObject(hHairImage);
}

void Player::UpdateFrame()
{
    // timer 클래스 사용
    playerTimer->Update();       // getDeltaTime 고정
    playerTimer->UpdateFPS();

    timePerSecond += playerTimer->getDeltaTime();

    cout.precision(1);
    //std::cout << "Time: " << timePerSecond << "s" << std::endl;
    
    if (getViewDir() == PAUSE)
    {
        if (timePerSecond >= 0.5)
        {
            curframe++;
            timePerSecond = 0;
        }
    }
    else
    {
        if (timePerSecond >= 0.3)
        {
            curframe++;
            timePerSecond = 0;
        }
    }
   
    //cout << "curframe: " << curframe << endl;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;
}

void Player::Move()
{
    // CPU 처리 속도와 무관하게 동일한 거리로 움직임
    setDistance(speed * playerTimer->getDeltaTime());

    Vec2 pPos = getPosition();

    if (GetAsyncKeyState('A') & 0x8000)
    {
        viewDir = LEFT;
        // 충돌상태에서 벗어나게하기
        if (preViewDir != viewDir)      setCollided(false, preViewDir);
        
        // 충돌X, 거리 변화O
        if (!isCollidedL)                pPos.x -= getDistance();
        // 충돌O, 충돌체 방향으로 향할때 거리 변화X
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

        preViewDir = LEFT;
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        viewDir = RIGHT;
        if (preViewDir != viewDir)      setCollided(false, preViewDir);

        if (!isCollidedR)               pPos.x += getDistance();
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

        preViewDir = RIGHT;
    }
    else if (GetAsyncKeyState('W') & 0x8000)
    {
        viewDir = UP;
        if (preViewDir != viewDir)      setCollided(false, preViewDir);

        if (!isCollidedU)               pPos.y -= getDistance();
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

        preViewDir = UP;
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
        viewDir = DOWN;
        if (preViewDir != viewDir)      setCollided(false, preViewDir);

        if (!isCollidedD)               pPos.y += getDistance();
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

       preViewDir = DOWN;
    }
    else
        viewDir = PAUSE;

    if (viewDir != PAUSE)
        setPosition(pPos);
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
    Move();
    UpdateFrame();
    setRect({ (LONG)getPosition().x - 1, (LONG)getPosition().y + 5, }, { (LONG)getPosition().x + 43, (LONG)getPosition().y + 80 });
}

