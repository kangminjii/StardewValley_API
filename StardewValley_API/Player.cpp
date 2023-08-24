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

        if (hAniImage1 == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�ִϸ��̼�1 �̹��� �ε� ����"), TEXT("����"), MB_OK);
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

        if (hAniImage2 == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�ִϸ��̼�2 �̹��� �ε� ����"), TEXT("����"), MB_OK);
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
		hMemDC = CreateCompatibleDC(hdc); // ���� ����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage1);
		bx = bitAni1.bmWidth / SPRITE_FRAME_COUNT_X; // ��ü �ʺ�
		by = bitAni1.bmHeight / SPRITE_FRAME_COUNT_Y; // ��ü ����

		int xStart = curframe * bx;
		int yStart = 0;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// left
	else if (getViewDir() == LEFT || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // ���� ����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage1);
		bx = bitAni1.bmWidth / SPRITE_FRAME_COUNT_X; // ��ü �ʺ�
		by = bitAni1.bmHeight / SPRITE_FRAME_COUNT_Y; // ��ü ����

		int xStart = curframe * bx;
		int yStart = by;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// up
	else if (getViewDir() == UP || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // ���� ����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage2);
		bx = bitAni2.bmWidth / SPRITE_FRAME_COUNT_X; // ��ü �ʺ�
		by = bitAni2.bmHeight / SPRITE_FRAME_COUNT_Y; // ��ü ����

		int xStart = curframe * bx;
		int yStart = 0;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 42, 90, hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// right
	else if (getViewDir() == RIGHT || getViewDir() == PAUSE)
	{
		hMemDC = CreateCompatibleDC(hdc); // ���� ����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage2);
		bx = bitAni2.bmWidth / SPRITE_FRAME_COUNT_X; // ��ü �ʺ�
		by = bitAni2.bmHeight / SPRITE_FRAME_COUNT_Y; // ��ü ����

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
    // CPU ó�� �ӵ��� �����ϰ� ������ �Ÿ��� ������
    setDistance(speed * playerTimer->getDeltaTime());

    Vec2 pPos = getPosition();

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        viewDir = LEFT;
        // �浹���¿��� ������ϱ�
        if (preViewDir != viewDir)      setCollided(false, preViewDir);
        
        // �浹X, �Ÿ� ��ȭO
        if (!isCollidedL)               pPos.x -= getDistance();
        // �浹O, �浹ü �������� ���Ҷ� �Ÿ� ��ȭX
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
    // timer Ŭ���� ���
    playerTimer->Update();       // getDeltaTime ����
    playerTimer->UpdateFPS();

    Move();
    setRect({ (LONG)getPosition().x - 1, (LONG)getPosition().y + 5, }, { (LONG)getPosition().x + 43, (LONG)getPosition().y + 80 });
}

