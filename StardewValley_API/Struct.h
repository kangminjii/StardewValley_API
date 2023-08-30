#pragma once

// 1pixel당 불러오는 횟수가 많아서 사용자의 위치를 POINT로 지정시 너무 빠른 속도로 움직임
// > float형으로 변환하기 위한 헤더

struct Vec2
{
	float x;
	float y;

public:
	Vec2()
		: x(0.f), y(0.f)
	{}

	Vec2(int _x, int _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2 operator-(int _x)
	{
		return Vec2(x - _x, y - _x);
	}
};