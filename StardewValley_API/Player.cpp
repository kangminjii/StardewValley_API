#include "Define.h"
#include "Player.h"

Player::Player()
    : position{ 100, 100}, prevPosition{ 0, 0 }, viewDir(NONE), preViewDir(NONE), speed(200.f), distance(0), startRect{ 0,0 }, endRect{ 0,0 },
    isCollidedL(false), isCollidedR(false), isCollidedU(false), isCollidedD(false), cursorPos{ 0, 0 },
    hAniImage1(0), hAniImage2(0)
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
    // >> : animation
    { // down & left
        hAniImage1 = (HBITMAP)LoadImage(NULL, TEXT("images/test1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage1 == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("애니메이션1 이미지 로드 에러"), TEXT("에러"), MB_OK);
            return;
        }

        GetObject(hAniImage1, sizeof(BITMAP), &bitAni1);

        RUN_FRAME_MAX = bitAni1.bmWidth / SPRITE_SIZE_X - 1; // 8
        RUN_FRAME_MIN = 1;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni1.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni1.bmHeight / SPRITE_SIZE_Y;
    }

    { // up & right
        hAniImage2 = (HBITMAP)LoadImage(NULL, TEXT("images/test2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage2 == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("애니메이션2 이미지 로드 에러"), TEXT("에러"), MB_OK);
            return;
        }

        GetObject(hAniImage2, sizeof(BITMAP), &bitAni2);

        RUN_FRAME_MAX = bitAni2.bmWidth / SPRITE_SIZE_X - 1; // 8
        RUN_FRAME_MIN = 1;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni2.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni2.bmHeight / SPRITE_SIZE_Y;
    }
}
void Player::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	// down
	if (getViewDir() == DOWN || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage1);
		bx = bitAni1.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
		by = bitAni1.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

		int xStart = curframe * bx;
		int yStart = 0;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// left
	else if (getViewDir() == LEFT || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage1);
		bx = bitAni1.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
		by = bitAni1.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

		int xStart = curframe * bx;
		int yStart = by;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// up
	else if (getViewDir() == UP || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage2);
		bx = bitAni2.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
		by = bitAni2.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

		int xStart = curframe * bx;
		int yStart = 0;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// right
	else if (getViewDir() == RIGHT || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // 같은 포맷
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage2);
		bx = bitAni2.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
		by = bitAni2.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

		int xStart = curframe * bx;
		int yStart = by;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}
void Player::DeleteBitmap()
{
    DeleteObject(hAniImage1);
    DeleteObject(hAniImage2);
}

void Player::Move()
{
    // CPU 처리 속도와 무관하게 동일한 거리로 움직임
    setDistance(speed * playerTimer->getDeltaTime());

    Vec2 pPos = getPosition();

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        viewDir = LEFT;
        // 충돌상태에서 벗어나게하기
        if (preViewDir != viewDir)      setCollided(false, preViewDir);
        
        // 충돌X, 거리 변화O
        if (!isCollidedL)               pPos.x -= getDistance();
        // 충돌O, 충돌체 방향으로 향할때 거리 변화X
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

        preViewDir = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        viewDir = RIGHT;
        if (preViewDir != viewDir)      setCollided(false, preViewDir);

        if (!isCollidedR)               pPos.x += getDistance();
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

        preViewDir = RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        viewDir = UP;
        if (preViewDir != viewDir)      setCollided(false, preViewDir);

        if (!isCollidedU)               pPos.y -= getDistance();
        else if (viewDir == preViewDir) setPosition(getPrevPosition());

        preViewDir = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
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
    // timer 클래스 사용
    playerTimer->Update();       // getDeltaTime 고정
    playerTimer->UpdateFPS();

    Move();
    setRect({ (LONG)getPosition().x - 1, (LONG)getPosition().y + 5, }, { (LONG)getPosition().x + 43, (LONG)getPosition().y + 80 });
}

