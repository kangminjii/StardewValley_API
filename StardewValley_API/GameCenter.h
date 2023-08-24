#pragma once
#pragma comment(lib, "msimg32.lib")
#include "Player.h"
#include "Item.h"
#include "Define.h"

class GameCenter
{
	MyCore(GameCenter); // 싱글톤 패턴

private:
	HWND m_hWnd;			// 메인 윈도우 핸들
	POINT m_ptResolution;	// 메인 윈도우 해상도
	HDC m_hdc;				// 메인 윈도우에 그릴 DC

	// 더블 버퍼링
	RECT rectView;
	HBITMAP hDoubleBufferImage;

	// 배경
	HBITMAP hMapImage;
	BITMAP  bitMap;

private:
	Player player;
	std::list<Item*> itemList;

public:
	// player : 플레이어 객체 불러오기
	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// item : 아이템리스트 객체 불러오기
	void setItemList() { addItem(); }
	std::list<Item*>& getItemList() { return itemList; }

public:

	// 초기화
	int Init(HWND g_hWnd, POINT p);

	// 광질하는지 체크
	int isMining(HWND hWnd);

	// 아이템 관리
	void addItem();
	void deleteItem();

	// >> : 반복적으로 체크해주는 함수
	void Update();
	void OnCollision();

//// 더블 버퍼링
private:
	int SPRITE_SIZE_X = 27; // x 길이 256
	int SPRITE_SIZE_Y = 60; // y 길이 256

	int RUN_FRAME_MAX = 0;
	int RUN_FRAME_MIN = 0;
	int curframe = RUN_FRAME_MIN;

	int SPRITE_FRAME_COUNT_X = 0;
	int SPRITE_FRAME_COUNT_Y = 0;

public:
	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HWND m_hWnd, HDC hdc);
	void DeleteBitmap();
	void UpdateFrame(HWND m_hWnd);

	// 타이머 함수
	VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
};

