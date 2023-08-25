#include "Timer.h"
#include <cmath>
#include <timeapi.h>
#include "Define.h"

#pragma comment(lib, "winmm.lib")


Timer::Timer()
{
	// microsecond까지 측정하여 정확한 시간값을 저장하기 위해 large_integer 사용

	// 1초동안 CPU의 진동수(주파수)를 반환하는 함수(고정값)
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	// 현재 CPU의 클럭스룰 얻는 함수
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	
	if (lastTime == NULL)	lastTime = 0;
	
	//컴퓨터는 곱셈연산이 빠르므로 역수로 미리 만듦
	timeScale = 1.0 / (double)periodFrequency;
	deltaTime = 0;
	curTime = 0;
	fps = 0;
}

void Timer::Update()
{
	// 현재 프레임 진동수(CPU 클러수) 저장
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	// deltaTime(프레임 사이의 시간) = (현재 프레임 진동수 - 이전 프레임 진동수)/초당진동수

	deltaTime = abs((float)(curTime - lastTime) * timeScale);
	lastTime = curTime;

}

float Timer::getDeltaTime()
{
	return deltaTime;
}

void Timer::UpdateFPS()
{
	static DWORD frameCount = 0;		// 프레임 카운트 수
	static float timeElapsed = 0.0f;	// 흐른 시간
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