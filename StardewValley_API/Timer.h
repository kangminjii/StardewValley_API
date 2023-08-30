#pragma once
#include "Define.h"

class Timer
{
private:
	__int64 periodFrequency;
	__int64 curTime;
	__int64 lastTime;
	
	float deltaTime; // 1프레임당 시간
	float timeScale;

	float fps;

public:
	float getDeltaTime() { return deltaTime; }
	float getFPS() { return fps; }

public:
	Timer();
	void Update();
	void UpdateFPS();
};