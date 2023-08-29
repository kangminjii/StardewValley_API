#pragma once
#pragma comment(lib, "msimg32.lib")
#include "Define.h"
#include "Player.h"
#include "Item.h"
#include "Tilemap.h"

class GameCenter
{
	MyCore(GameCenter); // �̱��� ����

private:
	HWND m_hWnd;			// ���� ������ �ڵ�
	POINT m_ptResolution;	// ���� ������ �ػ�
	HDC m_hdc;				// ���� �����쿡 �׸� DC

private:
	Player player;
	std::list<Item*> itemList;
	Tilemap tilemap;

public:
	// player : �÷��̾� ��ü �ҷ�����
	void setPlayer(Player p) { player = p; }
	Player getPlayer() { return player; }

	// item : �����۸���Ʈ ��ü �ҷ�����
	void setItemList() { addItem(); }
	std::list<Item*>& getItemList() { return itemList; }

	// tilemap : ����� tile��
	Tilemap getTilemap() { return tilemap; }

public:
	// �ʱ�ȭ
	int Init(HWND g_hWnd, POINT p);

	// �����ϴ��� üũ
	void isMining(HWND hWnd);

	// ������ ����
	void addItem();
	void deleteItem();

	// �ݺ������� üũ���ִ� �Լ�
	void Update();
	void OnCollision();


//// ���� ���۸�
private:
	RECT rectView;
	HBITMAP hDoubleBufferImage;

	// �κ��丮
	HBITMAP hInvenImage;
	BITMAP bitInven;

public:
	void DrawBitmapDoubleBuffering(HWND m_hWnd, HDC hdc);
	void DeleteBitmap();


	// �� �о����
public:
	void SaveTile();
	void LoadTile();
};

