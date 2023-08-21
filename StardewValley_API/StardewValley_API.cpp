// StardewValley_API.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "StardewValley_API.h"
#include "GameCenter.h"
#include <vector>

#define MAX_LOADSTRING 100
#define timer_ID_1 11
#define timer_ID_2 12


// >> : BITMAP
#pragma comment(lib, "msimg32.lib")

RECT rectView;

// 배경
HBITMAP hFloorImage;
BITMAP  bitFloor;

HBITMAP hWallImage;
BITMAP  bitWall;

// 돌
HBITMAP hStoneImage;
BITMAP  bitStone;


// << : BITMAP

// >> : ANI
HBITMAP hAniImage1;
BITMAP bitAni1;
HBITMAP hAniImage2;
BITMAP bitAni2;

//const int SPRITE_SIZE_X = 40; // x 길이 256
//const int SPRITE_SIZE_Y = 64; // y 길이 256
const int SPRITE_SIZE_X = 27; // x 길이 256
const int SPRITE_SIZE_Y = 60; // y 길이 256

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;
int curframe = RUN_FRAME_MIN;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;
// << : ANI

// >> : FUNC
void CreateBitmap();
void DeleteBitmap();
void UpdateFrame(HWND hWnd);
// << : FUNC

// >> : Double Buffering
HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
// << : Double Buffering

// 객체 선언
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);


// >> : Item
// 1 tile(길이 10)당 좌표로 저장
vector<POINT> tilemap;
void CreateTilemap();



VOID CALLBACK CheckCollision(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime); // 충돌체크

GameCenter GC;



#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STARDEWVALLEYAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 게임센터(주인공과 충돌체들 부르는 객체)
    //GameCenter GC;


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STARDEWVALLEYAPI));

    MSG msg;

    //// 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    // PeekMessage를 통해 메시지가 들어올때 바로 사용되게끔 작동시킴
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 코드 동작 부분
            //GC.Update();

        }
    }
   
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STARDEWVALLEYAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STARDEWVALLEYAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      500, 200, 1000, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    
    switch (message)
    {
    case WM_CREATE: // 초기화 값 세팅
    {

        CreateTilemap();

        // animation
        CreateBitmap();
        GetClientRect(hWnd, &rectView);
        SetTimer(hWnd, timer_ID_1, 300, AniProc);
        SetTimer(hWnd, timer_ID_2, 100, CheckCollision);
    }
    break;
    case WM_TIMER: // 타이머 이벤트, 타이머는 일이 바쁘지 않을때만 잘 작동됨
    {
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_KEYDOWN:
    {
        GC.Update();
        InvalidateRect(hWnd, NULL, FALSE);
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        DrawBitmapDoubleBuffering(hWnd, hdc);


        EndPaint(hWnd, &ps); 
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, timer_ID_1);
        DeleteBitmap();
        PostQuitMessage(0);
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void CreateTilemap()
{
    // 사이즈 10인 칸들
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            tilemap.push_back({ i, j });
        }
    }
}


void CreateBitmap()
{
    // >> : wall
    {
        hWallImage = (HBITMAP)LoadImage(NULL, TEXT("images/map_wall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hWallImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러4"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hWallImage, sizeof(BITMAP), &bitWall);
    }
    // <<

    // floor
    {
        hFloorImage = (HBITMAP)LoadImage(NULL, TEXT("images/map_floor.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hFloorImage, sizeof(BITMAP), &bitFloor);
    }
    // <<
    
    // >> : animation
    { // down & left
        hAniImage1 = (HBITMAP)LoadImage(NULL, TEXT("images/test1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hAniImage1, sizeof(BITMAP), &bitAni1);

        // :
        RUN_FRAME_MAX = bitAni1.bmWidth / SPRITE_SIZE_X - 1; // 8
        RUN_FRAME_MIN = 1;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni1.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni1.bmHeight / SPRITE_SIZE_Y;
    }

    { // up & right
        hAniImage2 = (HBITMAP)LoadImage(NULL, TEXT("images/test2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hAniImage2, sizeof(BITMAP), &bitAni2);

        // :
        RUN_FRAME_MAX = bitAni2.bmWidth / SPRITE_SIZE_X - 1; // 8
        RUN_FRAME_MIN = 1;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni2.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni2.bmHeight / SPRITE_SIZE_Y;
    }
    // <<

    // >> : item(stone)
    {
        hStoneImage = (HBITMAP)LoadImage(NULL, TEXT("images/stones.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        GetObject(hStoneImage, sizeof(BITMAP), &bitStone);

        //SPRITE_FRAME_COUNT_X = bitStone.bmWidth / 24;
        //SPRITE_FRAME_COUNT_Y = bitStone.bmHeight / 12;
    }
    // << 

}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //  기본은 검정색

    // >> : wall
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hWallImage);
        bx = bitWall.bmWidth; // 전체 너비
        by = bitWall.bmHeight; // 전체 높이

        // 이미지 확대
        StretchBlt(hMemDC, 0, -100, 4000, 3200, hMemDC2, 0, 0, 1000, 800, SRCCOPY);

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // << 
    
    // >> :floor
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hFloorImage);
        bx = bitFloor.bmWidth; // 전체 너비
        by = bitFloor.bmHeight; // 전체 높이

        // 이미지 확대
        StretchBlt(hMemDC, 150, 250, 2500, 1500, hMemDC2, 0, 0, 1000, 800, SRCINVERT);

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // <<
   
    // >> : animation
    // down
    if (GC.getPlayer().getViewDir() == DOWN || GC.getPlayer().getViewDir() == PAUSE)
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage1);
        bx = bitAni1.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni1.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = 0;

        TransparentBlt(hMemDC, GC.getPlayer().getPositionX(), GC.getPlayer().getPositionY(), bx, by, hMemDC2, xStart, yStart, bx, by, RGB(0, 0, 0));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // left
    else if (GC.getPlayer().getViewDir() == LEFT || GC.getPlayer().getViewDir() == PAUSE)
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage1);
        bx = bitAni1.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni1.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = by;

        TransparentBlt(hMemDC, GC.getPlayer().getPositionX(), GC.getPlayer().getPositionY(), bx, by, hMemDC2, xStart, yStart, bx, by, RGB(0, 0, 0));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // up
    else if (GC.getPlayer().getViewDir() == UP || GC.getPlayer().getViewDir() == PAUSE)
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage2);
        bx = bitAni2.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni2.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = 0;

        TransparentBlt(hMemDC, GC.getPlayer().getPositionX(), GC.getPlayer().getPositionY(), bx, by, hMemDC2, xStart, yStart, bx, by, RGB(0, 0, 0));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // right
    else if (GC.getPlayer().getViewDir() == RIGHT || GC.getPlayer().getViewDir() == PAUSE)
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage2);
        bx = bitAni2.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni2.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = by;

        TransparentBlt(hMemDC, GC.getPlayer().getPositionX(), GC.getPlayer().getPositionY(), bx, by, hMemDC2, xStart, yStart, bx, by, RGB(0, 0, 0));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // <<

    // > : stone1
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hStoneImage);
        bx = bitStone.bmWidth / 24; 
        by = bitStone.bmHeight / 12; 

        int xStart = bx * 5; // 가로에 있는 순서대로 출력이 됨
        int yStart = by *5;

        for (auto it = GC.getItemList().begin(); it != GC.getItemList().end(); it++)
            TransparentBlt(hMemDC, (*it)->getPositionX(), (*it)->getPositionY(), bx, by, hMemDC2, xStart, yStart, bx, by, RGB(0, 0, 0));

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    GC.Render(hMemDC);

    


    // >> : hdc에 그려주기
    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void DeleteBitmap()
{
    DeleteObject(hAniImage1);
    DeleteObject(hAniImage2);
    DeleteObject(hWallImage);
    DeleteObject(hFloorImage);
    DeleteObject(hStoneImage);
}

void UpdateFrame(HWND hWnd)
{
    curframe++;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (GC.getPlayer().getViewDir() != PAUSE && idEvent == timer_ID_1)
    {
        UpdateFrame(hWnd);
    }
    
}

// 계속 충돌 체크해주는 업데이트문
VOID CALLBACK CheckCollision(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (idEvent == timer_ID_2)
    {
        //GC.getPlayer().CollisionCheck();
    }
}

