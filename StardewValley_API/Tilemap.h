#pragma once
#include "Define.h"

const int ROW = 20;
const int COL = 25;

class Tilemap
{
private:
	vector<vector<POINT>> tiles;	// ��ġ
	POINT position;

	// ������۸�
	HBITMAP hMapImage;
	BITMAP  bitMap;

	HBITMAP hBackImage;
	BITMAP  bitBack;

public:
	// Tile
	void setTiles();
	vector<vector<POINT>> getTiles() { return tiles; }
	
	// �� Tile�� ��ġ��ǥ
	void setPosition(POINT po) { position = po; }
	POINT getPosition() { return position; }

public:
	Tilemap();
	~Tilemap();

	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HDC hdc);
	void DeleteBitmap();


	// Ÿ�ϸ� ���Ͽ� ����
public:
	void SaveTile();
	void LoadTile();



};