// StardewValley_API.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "StardewValley_API.h"

#define MAX_LOADSTRING 100
#define timer_ID_1 11
#define timer_ID_2 12

RECT rectView;

// >> : BITMAP
#pragma comment(lib, "msimg32.lib")

HBITMAP hBackImage;
BITMAP  bitBack;

HBITMAP hFrontImage;
BITMAP  bitFront;

// << : BITMAP

// >> : ANI
HBITMAP hAniImage;
BITMAP bitAni;
const int SPRITE_SIZE_X = 57;
const int SPRITE_SIZE_Y = 52;

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
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
// << : FUNC

// >> : Double Buffering
HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
// << : Double Buffering




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

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STARDEWVALLEYAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    static POINT ptCurPos;

    switch (message)
    {
    case WM_CREATE: // 초기화 값 세팅
        ptCurPos.x = 0;
        ptCurPos.y = 0;
        GetClientRect(hWnd, &rectView);
        CreateBitmap();
        SetTimer(hWnd, timer_ID_1, 30, AniProc);
        break;
    case WM_TIMER: // 타이머 이벤트, 타이머는 일이 바쁘지 않을때만 잘 작동됨
    {
        if (wParam == timer_ID_1)
        {
            ptCurPos.x += 20;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
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

void CreateBitmap()
{
    // >> : front
    // wall
    {
        hFrontImage = (HBITMAP)LoadImage(NULL, TEXT("images/map_wall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hFrontImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러4"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hFrontImage, sizeof(BITMAP), &bitFront);
    }
    // <<
    
    // >> : background 
    // floor
    {
        hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/map_floor.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hBackImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러1"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hBackImage, sizeof(BITMAP), &bitBack);
    }

    // >> : animation
    {
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL) // 이미지가 출력되지 않을 때
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러3"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        // :
        RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1;
        RUN_FRAME_MIN = 2;
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;
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

    // >> : front
    // wall
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hFrontImage);
        bx = bitFront.bmWidth; // 전체 너비
        by = bitFront.bmHeight; // 전체 높이

        StretchBlt(hMemDC, 0, -100, 4000, 3200, hMemDC2, 0, 0, 1000, 800, SRCCOPY);
        //BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // << : front
    
    // >> : background
    // floor
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
        bx = bitBack.bmWidth; // 전체 너비
        by = bitBack.bmHeight; // 전체 높이

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC2, hBrush);

        //Ellipse(hMemDC2, 500, 0, 1000, 1000);

        SelectObject(hMemDC2, oldBrush);
        DeleteObject(hBrush);

        // 그림 그리기
        //BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCPAINT); 
        // 이미지 확대
        StretchBlt(hMemDC, 200, 250, 2000, 1200, hMemDC2, 0, 0, 1000, 800, SRCINVERT);
        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // >> : animation
    {
        hMemDC2 = CreateCompatibleDC(hMemDC); // 같은 포맷
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X; // 전체 너비
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y; // 전체 높이

        int xStart = curframe * bx;
        int yStart = 0;

        static int xPos = 0;
        TransparentBlt(hMemDC, 150 + xPos, 250, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255)); // 배경의 분홍색만 사라지게 함

        // 애니메이션 1개 더 생성
        //StretchBlt(hMemDC, 150 + xPos, 300, -bx, by, hMemDC2, xStart, yStart, bx, by, SRCCOPY);

        //xPos++;
        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }
    // <<

   
    

    // >> : hdc에 그려주기
    //BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
    TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hBackImage);
}

void UpdateFrame(HWND hWnd)
{
    curframe++;
    if (curframe > RUN_FRAME_MAX)
        curframe = RUN_FRAME_MIN;

    InvalidateRect(hWnd, NULL, FALSE);
}

static int yPos = 0;
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    yPos += 5;
    if (yPos > rectView.bottom) yPos = 0;
}