#pragma once

// 1pixel�� �ҷ����� Ƚ���� ���Ƽ� ������� ��ġ�� POINT�� ������ �ʹ� ���� �ӵ��� ������
// > float������ ��ȯ�ϱ� ���� ���

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