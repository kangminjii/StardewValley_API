#pragma once
#pragma comment(lib, "msimg32.lib")
#include "Player.h"
#include "Item.h"
#include "Define.h"

class GameCenter
{
	MyCore(GameCenter); // �̱��� ����

private:
	HWND m_hWnd;			// ���� ������ �ڵ�
	POINT m_ptResolution;	// ���� ������ �ػ�
	HDC m_hdc;				// ���� �����쿡 �׸� DC

	// ���� ���۸�
	RECT rectView;
	HBITMAP hDoubleBufferImage;

	// ���
	HBITMAP hMapImage;
	BITMAP  bitMap;

private:
	Player player;
	std::list<Item*> itemList;

public:
	// player : �÷��̾� ��ü �ҷ�����
	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// item : �����۸���Ʈ ��ü �ҷ�����
	void setItemList() { addItem(); }
	std::list<Item*>& getItemList() { return itemList; }

public:

	// �ʱ�ȭ
	int Init(HWND g_hWnd, POINT p);

	// �����ϴ��� üũ
	int isMining(HWND hWnd);

	// ������ ����
	void addItem();
	void deleteItem();

	// >> : �ݺ������� üũ���ִ� �Լ�
	void Update();
	void OnCollision();

//// ���� ���۸�
private:
	int SPRITE_SIZE_X = 27; // x ���� 256
	int SPRITE_SIZE_Y = 60; // y ���� 256

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

	// Ÿ�̸� �Լ�
	VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
};

