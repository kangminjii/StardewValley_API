#pragma once
#include "Define.h"

const int ROW = 20;
const int COL = 25;

class Tilemap
{
private:
	vector<vector<POINT>> tiles;	// 위치
	POINT position;

	// 더블버퍼링
	HBITMAP hMapImage;
	BITMAP  bitMap;

	HBITMAP hBackImage;
	BITMAP  bitBack;

public:
	// Tile
	void setTiles();
	vector<vector<POINT>> getTiles() { return tiles; }
	
	// 각 Tile의 위치좌표
	void setPosition(POINT po) { position = po; }
	POINT getPosition() { return position; }

public:
	Tilemap();
	~Tilemap();

	void CreateBitmap();
	void DrawBitmapDoubleBuffering(HDC hdc);
	void DeleteBitmap();


	// 타일맵 파일에 저장
public:
	void SaveTile();
	void LoadTile();



};