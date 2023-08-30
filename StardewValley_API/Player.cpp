#include "Define.h"
#include "Player.h"

Player::Player()
    : position{ 300, 100 }, prevPosition{ 0, 0 }, viewDir(NONE)/*, preViewDir(NONE),*/, speed(250.f), distance(0), startRect{ 0,0 }, endRect{ 0,0 },
    isCollidedL(false), isCollidedR(false), isCollidedU(false), isCollidedD(false), cursorPos{ 0, 0 }, mineTimeChecked(false), isMining(false), miningCycle(0),
    hAniImage(0), hAniLeftImage(0), hShirtImage(0), hHairImage(0), hHairLeftImage(0)
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

        if (hAniImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�ִϸ��̼�1 �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        curframe = 0; // 0~1 frame
        curframeMine = 0; // 0~4 frame
    }
    // player animation > �¿������Ų ����
    {
        hAniLeftImage = (HBITMAP)LoadImage(NULL, TEXT("images/playerLeft.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�ִϸ��̼�1-1 �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hAniLeftImage, sizeof(BITMAP), &bitAniLeft);

        curframe = 0; // 0~1 frame
    }

    // shirts
    {
        hShirtImage = (HBITMAP)LoadImage(NULL, TEXT("images/shirts.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hShirtImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("���� �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hShirtImage, sizeof(BITMAP), &bitShirt);
    }

    // hairs
    {
        hHairImage = (HBITMAP)LoadImage(NULL, TEXT("images/hair.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hHairImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�Ӹ� �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hHairImage, sizeof(BITMAP), &bitHair);
    }
    // hairs > �¿������Ų ����
    {
        hHairLeftImage = (HBITMAP)LoadImage(NULL, TEXT("images/hairLeft.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hHairLeftImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("�Ӹ����� �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hHairLeftImage, sizeof(BITMAP), &bitHairLeft);
    }

    // Tools
    {
        hToolImage = (HBITMAP)LoadImage(NULL, TEXT("images/tools.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hToolImage == NULL) // �̹����� ��µ��� ���� ��
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, TEXT("���� �̹��� �ε� ����"), TEXT("����"), MB_OK);
            return;
        }

        GetObject(hToolImage, sizeof(BITMAP), &bitTool);
    }


}

void Player::DrawBitmapDoubleBuffering(HDC hdc)
{
    HDC hMemDC = CreateCompatibleDC(hdc);

    HBITMAP hAniBitmap, hAniLeftBitmap, hShirtBitmap, hHairBitmap, hHairLeftBitmap;
    HBITMAP hToolBitmap;

    // AniImage ����
    int bx1 = bitAni.bmWidth / 23;
    int by1 = bitAni.bmHeight / 20;

    // ���� ����
    int bx2 = bitShirt.bmWidth / 15;
    int by2 = bitShirt.bmHeight / 27;

    // �Ӹ� ����
    int bx3 = bitHair.bmWidth / 8;
    int by3 = bitHair.bmHeight / 12;

    // ���� ����
    int bx4 = bitTool.bmWidth / 21;
    int by4 = bitTool.bmHeight / 12;

    //// ������ �ִϸ��̼�
    //down
    if (getViewDir() == DOWN)
    {
        // ��-����
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = curframe * bx1;           // ��
        int xStart2 = (curframe + 18) * bx1;    // ����
        int yStart1 = by1 * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // ����
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2�� ���� ���� ����
        int yStart3 = 0;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // ��
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 6) * bx1;      // ��

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // �Ӹ�
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 6;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 15, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
    }
    // left
    else if (getViewDir() == LEFT)
    {
        // ��-����
        hAniLeftBitmap = (HBITMAP)SelectObject(hMemDC, hAniLeftImage);
        int xStart1 = (curframe + 20) * bx1;     // ��
        int xStart2 = (curframe + 2) * bx1; // ����
        int yStart1 = by1 * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // ����
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2�� ���� ���� ����
        int yStart3 = by2 * 2;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // ��
        hAniLeftBitmap = (HBITMAP)SelectObject(hMemDC, hAniLeftImage);
        int xStart4 = (curframe + 14) * bx1; // ��

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // �Ӹ�
        hHairLeftBitmap = (HBITMAP)SelectObject(hMemDC, hHairLeftImage);
        int xStart5 = bx3 * 6;
        int yStart5 = by3 * 7;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 22, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairLeftBitmap);
        DeleteDC(hMemDC);
    }
    // up
    else if (getViewDir() == UP)
    {
        // ��-����
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = (curframe + 4) * bx1;     // ��
        int xStart2 = (curframe + 22) * bx1;    // ����
        int yStart1 = by1 * 3 - 1;

        if (xStart2 + bx1 >= bitAni.bmWidth)    xStart2 = bitAni.bmWidth - 16;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // ����
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2�� ���� ���� ����
        int yStart3 = by2 * 3;

        TransparentBlt(hdc, getPosition().x + 10, getPosition().y + 36, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // ��
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 10) * bx1; // ��
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // �Ӹ�
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
        // ��-����
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = (curframe + 2) * bx1;     // ��
        int xStart2 = (curframe + 20) * bx1; // ����
        int yStart1 = by1 * 3 - 1;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x - 2, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // ����
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2�� ���� ���� ����
        int yStart3 = by2;

        TransparentBlt(hdc, getPosition().x + 8, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // ��
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframe + 8) * bx1; // ��

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // �Ӹ�
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 7;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 22, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
    }
    else if (!isMining && getViewDir() == PAUSE)
    {
        // ��-����
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = 0;           // ��
        int xStart2 = 18 * bx1;    // ����
        int yStart1 = 0;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // ����
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2�� ���� ���� ����
        int yStart3 = 0;

        TransparentBlt(hdc, getPosition().x + 11, getPosition().y + 40, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // ��
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = 6 * bx1;   // ��

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // �Ӹ�
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 6;

        TransparentBlt(hdc, getPosition().x, getPosition().y - 15, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
    }
    //// ���� �ִϸ��̼�
    else if (isMining)
    {
        // Right
        // ��-����
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart1 = curframeMine * bx1;           // ��
        int xStart2 = (curframeMine + 18) * bx1;    // ����
        int yStart1 = by1 * 8 - 6;

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart1, yStart1, bx1, by1, RGB(0, 0, 0));
        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart2, yStart1, bx1, by1, RGB(0, 0, 0));

        // ����
        hShirtBitmap = (HBITMAP)SelectObject(hMemDC, hShirtImage);
        int xStart3 = 0;  // *bx2�� ���� ���� ����
        int yStart3 = by2;

        if (curframeMine == 4)
            TransparentBlt(hdc, getPosition().x + 8, getPosition().y + 40 - 2 * 4, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));
        else
            TransparentBlt(hdc, getPosition().x + 8, getPosition().y + 40 - curframeMine * 4, 23, 21, hMemDC, xStart3, yStart3, bx2, by2, RGB(0, 0, 0));

        // ����
        hToolBitmap = (HBITMAP)SelectObject(hMemDC, hToolImage);
        int xStart6 = bx4 * 2;
        int yStart6 = by4 * 3;

        TransparentBlt(hdc, getPosition().x + 40, getPosition().y - 20, 33, 75, hMemDC, xStart6, yStart6, bx4, by4, RGB(0, 0, 0));

        // ��
        hAniBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
        int xStart4 = (curframeMine + 6) * bx1;      // ��

        TransparentBlt(hdc, getPosition().x, getPosition().y, 44, 100, hMemDC, xStart4, yStart1, bx1, by1, RGB(0, 0, 0));

        // �Ӹ�
        hHairBitmap = (HBITMAP)SelectObject(hMemDC, hHairImage);
        int xStart5 = bx3;
        int yStart5 = by3 * 7;

        if (curframeMine == 4)
            TransparentBlt(hdc, getPosition().x, getPosition().y - 24 - 2 * 4, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));
        else
            TransparentBlt(hdc, getPosition().x - 4, getPosition().y - 24 - curframeMine * 4, 44, 85, hMemDC, xStart5, yStart5, bx3, by3, RGB(0, 0, 0));

        SelectObject(hMemDC, hHairBitmap);
        DeleteDC(hMemDC);
    }



}

void Player::DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hAniLeftImage);
    DeleteObject(hShirtImage);
    DeleteObject(hHairImage);
    DeleteObject(hHairLeftImage);
}

void Player::UpdateFrame()
{
    // timer Ŭ���� ���
    playerTimer->Update();       // getDeltaTime ����
    playerTimer->UpdateFPS();

    timePerSecond += playerTimer->getDeltaTime();

    if (isMining)
    {
        isMining = false;

        if (timePerSecond >= 0.15)
        {
            cout << "curframeMine : " << curframeMine << endl;
            curframeMine++;

            if (curframeMine == 4)
                miningCycle++;

            timePerSecond = 0;
        }

        if (curframeMine == 4 && miningCycle == 2)
        {
            miningCycle = 0;
            mineTimeChecked = true;
        }
    }
    else if (getViewDir() == PAUSE)
    { // ���� �����ִ� �ִϸ��̼��� ����
        if (timePerSecond >= 1.5)
        {
            curframe++;
            timePerSecond = 0;
        }
    }
    else
    {   // �����϶�
        if (timePerSecond >= 0.3)
        {
            curframe++;
            timePerSecond = 0;
        }
    }

    if (curframe > 1)
        curframe = 0;
    if (curframeMine > 4)
        curframeMine = 0;
}

void Player::Move()
{
    // CPU ó�� �ӵ��� �����ϰ� ������ �Ÿ��� ������
    setDistance(speed * playerTimer->getDeltaTime());

    Vec2 pPos = getPosition();
    Vec2 distance = pPos - 5;

    if (GetAsyncKeyState('A') & 0x8000)
    {
        viewDir = LEFT;

        if (!isCollidedL)    // �浹X, �Ÿ� ��ȭO
            pPos.x -= getDistance();
        else            // �浹O, ���� ��ġ �ݴ밪���� ��ġ ����
            pPos.x += 3;
        
        setCollided(false, viewDir); //�浹���¿��� ������ϱ�
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        viewDir = RIGHT;

        if (!isCollidedR)   pPos.x += getDistance();
        else                pPos.x -= 3;

        setCollided(false, viewDir);
    }
    else if (GetAsyncKeyState('W') & 0x8000)
    {
        viewDir = UP;

        if (!isCollidedU)   pPos.y -= getDistance();
        else                pPos.y += 3;

        setCollided(false, viewDir);
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
        viewDir = DOWN;

        if (!isCollidedD)   pPos.y += getDistance();
        else                pPos.y -= 3;

        setCollided(false, viewDir);
    }
    else // pause
    {
        viewDir = PAUSE;
    }

    if (viewDir != PAUSE)
        setPosition(pPos);
}

void Player::Click(HWND hWnd)
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        isMining = true;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);
    }
    else
        curframeMine = 0;
}

void Player::UpdatePlayer()
{
    Move();
    UpdateFrame();
    setRect({ (LONG)getPosition().x - 1, (LONG)getPosition().y + 5, }, { (LONG)getPosition().x + 43, (LONG)getPosition().y + 95 });
}
