#include "Define.h"
#include "Player.h"

Player::Player()
    : position{ 300, 100}, prevPosition{ 0, 0 }, viewDir(NONE), preViewDir(NONE), speed(200.f), distance(0), startRect{ 0,0 }, endRect{ 0,0 },
    isCollidedL(false), isCollidedR(false), isCollidedU(false), isCollidedD(false), cursorPos{ 0, 0 },
    hAniImage(0), hShirtImage(0)
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
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/player.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�ִϸ��̼�1 �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        RUN_FRAME_MAX = (bitAni.bmWidth  / 8) / SPRITE_SIZE_X - 2; 
        RUN_FRAME_MIN = 0;
        curframe = RUN_FRAME_MIN; // 0~2 frame
    }

    { // shirts
        hShirtImage = (HBITMAP)LoadImage(NULL, TEXT("images/shirts.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hShirtImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�ִϸ��̼�2 �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hShirtImage, sizeof(BITMAP), &bitShirt);
    }
}
void Player::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx=0, by=0;

	// down
	if (getViewDir() == DOWN)
	{
		hMemDC = CreateCompatibleDC(hdc);

        // ��-����
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
		
        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����
		int xStart1 = curframe * bx;     // ��
        int xStart2 = (curframe + 6) * bx; // ��
        int xStart3 = (curframe + 18) * bx; // ����
        int yStart = by * 3 - 1;

		TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart, bx, by, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart3, yStart, bx, by, RGB(0, 0, 0));

        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
       
        // ����
        bx = bitAni.bmWidth / 46; // ��ü �ʺ�
        by = bitAni.bmHeight / 92; // ��ü ����
        int xStart = 0;
        int yStart1 = 0;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 41, 23, 20, hMemDC, xStart, yStart1, bx, by, RGB(0, 0, 0));

        // ��
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart, bx, by, RGB(0, 0, 0)); 


		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// left
	else if (getViewDir() == LEFT)
	{
        ///// �¿�����ʿ�
        hMemDC = CreateCompatibleDC(hdc);

        // ��-����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
       
        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����
        int xStart1 = (curframe + 2)* bx;     // ��
        int xStart2 = (curframe + 8) * bx; // ��
        int xStart3 = (curframe + 20) * bx; // ����
        int yStart = by * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart, bx, by, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart3, yStart, bx, by, RGB(0, 0, 0));

        // ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);

        bx = bitAni.bmWidth / 46; // ��ü �ʺ�
        by = bitAni.bmHeight / 92; // ��ü ����
        int xStart = 0;
        int yStart1 = by * 2;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 41, 23, 20, hMemDC, xStart, yStart1, bx, by, RGB(0, 0, 0));

        // ��
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart, bx, by, RGB(0, 0, 0));


        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
	}
	// up
	else if (getViewDir() == UP)
	{
        hMemDC = CreateCompatibleDC(hdc);

        // ��-����-��
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����
        int xStart1 = (curframe +4) * bx;     // ��
        int xStart2 = (curframe + 10) * bx; // ��
        int xStart3 = (curframe + 22) * bx; // ����
        int yStart = by * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart, bx, by, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart3, yStart, bx, by, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart, bx, by, RGB(0, 0, 0));

        // ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);

        bx = bitAni.bmWidth / 46; // ��ü �ʺ�
        by = bitAni.bmHeight / 85; // ��ü ����
        int xStart = 0;
        int yStart1 = by * 3;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 31, 25, 25, hMemDC, xStart, yStart1, bx, by, RGB(0, 0, 0));

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
	}
	// right
	else if (getViewDir() == RIGHT)
	{
        hMemDC = CreateCompatibleDC(hdc);

        // ��-����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����
        int xStart1 = (curframe + 2)* bx;     // ��
        int xStart2 = (curframe + 8) * bx; // ��
        int xStart3 = (curframe + 20) * bx; // ����
        int yStart = by * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart, bx, by, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart3, yStart, bx, by, RGB(0, 0, 0));

        // ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);

        bx = bitAni.bmWidth / 46; // ��ü �ʺ�
        by = bitAni.bmHeight / 92; // ��ü ����
        int xStart = 0;
        int yStart1 = by;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 39, 23, 20, hMemDC, xStart, yStart1, bx, by, RGB(0, 0, 0));

        // ��
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart, bx, by, RGB(0, 0, 0));


        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
	}
    else if (getViewDir() == PAUSE)
    {
        hMemDC = CreateCompatibleDC(hdc);

        // ��-����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����
        int xStart1 = (curframe + 4) * bx;     // ��
        int xStart2 = (curframe + 10) * bx; // ��
        int xStart3 = (curframe + 22) * bx; // ����
        int yStart = by * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart, bx, by, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart3, yStart, bx, by, RGB(0, 0, 0));

        // ����
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);

        bx = bitAni.bmWidth / 46; // ��ü �ʺ�
        by = bitAni.bmHeight / 92; // ��ü ����
        int xStart = 0;
        int yStart1 = by * 3;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 41, 23, 20, hMemDC, xStart, yStart1, bx, by, RGB(0, 0, 0));

        // ��
        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

        bx = bitAni.bmWidth / 23; // ��ü �ʺ�
        by = bitAni.bmHeight / 20; // ��ü ����

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart, bx, by, RGB(0, 0, 0));


        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
        }
}
void Player::DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hShirtImage);
}

void Player::UpdateFrame()
{
    // timer Ŭ���� ���
    playerTimer->Update();       // getDeltaTime ����
    playerTimer->UpdateFPS();

    timePerSecond += playerTimer->getDeltaTime();

    cout.precision(1);
    //std::cout << "Time: " << timePerSecond << "s" << std::endl;

    if (getViewDir() != PAUSE && timePerSecond >= 0.3)
    {
        curframe++;
        timePerSecond = 0;
    }
    cout << "curframe: " << curframe << endl;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;
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
    Move();
    UpdateFrame();
    setRect({ (LONG)getPosition().x - 1, (LONG)getPosition().y + 5, }, { (LONG)getPosition().x + 43, (LONG)getPosition().y + 80 });
}

