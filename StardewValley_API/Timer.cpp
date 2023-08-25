#include "Timer.h"
#include <cmath>
#include <timeapi.h>
#include "Define.h"

#pragma comment(lib, "winmm.lib")


Timer::Timer()
{
	// microsecond���� �����Ͽ� ��Ȯ�� �ð����� �����ϱ� ���� large_integer ���

	// 1�ʵ��� CPU�� ������(���ļ�)�� ��ȯ�ϴ� �Լ�(������)
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	// ���� CPU�� Ŭ������ ��� �Լ�
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	
	if (lastTime == NULL)	lastTime = 0;
	
	//��ǻ�ʹ� ���������� �����Ƿ� ������ �̸� ����
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

	deltaTime = abs((float)(curTime - lastTime) * timeScale);
	lastTime = curTime;

}

float Timer::getDeltaTime()
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