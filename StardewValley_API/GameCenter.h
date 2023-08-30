#pragma once
#pragma comment(lib, "msimg32.lib")
#include "Define.h"
#include "Player.h"
#include "Item.h"
#include "Tilemap.h"
#include "Tile.h"

class GameCenter
{
	MyCore(GameCenter); // 싱글톤 패턴

private:
	HWND m_hWnd;			// 메인 윈도우 핸들
	POINT m_ptResolution;	// 메인 윈도우 해상도
	HDC m_hdc;				// 메인 윈도우에 그릴 DC

private:
	Player player;
	std::list<Item*> itemList;
	//Tilemap tilemap;
	Tile tile;

public:
	// player : 플레이어 객체 불러오기
	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// item : 아이템리스트 객체 불러오기
	void setItemList() { addItem(); }
	std::list<Item*>& getItemList() { return itemList; }

	// tilemap : 배경의 tile들
	//Tilemap getTilemap() { return tilemap; }

public:
	// 초기화
	int Init(HWND g_hWnd, POINT p);

	// 광질하는지 체크
	void isMining(HWND hWnd);

	// 아이템 관리
	void addItem();
	void deleteItem();

	// 반복적으로 체크해주는 함수
	void Update();
	void OnCollision();


//// 더블 버퍼링
private:
	RECT rectView;
	HBITMAP hDoubleBufferImage;

	// 인벤토리
	HBITMAP hInvenImage;
	BITMAP bitInven;

	// 시작화면
	HBITMAP hStartImage;
	BITMAP bitStart;
	HBITMAP hBackImage;
	BITMAP bitBack;

public:
	void CreateBitmap(HDC hdc);
	void DrawBitmapDoubleBuffering(HDC hdc);
	void DeleteBitmap();

	// 씬전환
private:
	bool startScene = true; 
	void StartScene(HDC hdc);
	bool isTouched = false;
};

