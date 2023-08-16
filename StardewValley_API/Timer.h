#pragma once
#include <Windows.h>
#include <cmath>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

class Timer
{
private:

	__int64 periodFrequency;
	__int64 curTime;
	__int64 lastTime;
	
	double deltaTime;
	double timeScale;

	float fps;
public:

	Timer();
	void Update();
	void UpdateFPS();

	double getDeltaTime();
	float getFPS();

};

Timer::Timer()
{
	// microsecond���� �����Ͽ� ��Ȯ�� �ð����� �����ϱ� ���� large_integer ���
	
	// 1�ʵ��� CPU�� ������(���ļ�)�� ��ȯ�ϴ� �Լ�(������)
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	// ���� CPU�� Ŭ������ ��� �Լ�
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	
	// ��ǻ�ʹ� ���������� �����Ƿ� ������ �̸� ����
	timeScale = 1.0 / (double)periodFrequency;
	deltaTime = 0;
	curTime = 0;
	fps = 0;
}

void Timer::Update()
{
	// ���� ������ ������(CPU Ŭ����) ����
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	// deltaTime(������ ������ �ð�) = (���� ������ ������ - ���� ������ ������)/�ʴ�������

	deltaTime = abs((double)(curTime - lastTime) * timeScale);
	lastTime = curTime;
}

double Timer::getDeltaTime()
{
	return deltaTime;
}

void Timer::UpdateFPS()
{
	static DWORD frameCount = 0;		// ������ ī��Ʈ ��
	static float timeElapsed = 0.0f;	// �帥 �ð�
	static DWORD lastTime = timeGetTime();

	DWORD curTime = timeGetTime();
	float timeDelta = (curTime - lastTime) * 0.001f;

	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)
	{
		fps = (float)frameCount / timeElapsed;
		frameCount = 0;
		timeElapsed = 0.0f;
	}

	lastTime = curTime;
}

float Timer::getFPS()
{
	return fps;
}