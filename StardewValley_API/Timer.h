#pragma once
#include "Define.h"

class Timer
{
private:
	__int64 periodFrequency;
	__int64 curTime;
	__int64 lastTime;
	
	float deltaTime; // 1�����Ӵ� �ð�
	float timeScale;

	float fps;

public:
	float getDeltaTime();
	float getFPS();

public:
	Timer();
	void Update();
	void UpdateFPS();
};