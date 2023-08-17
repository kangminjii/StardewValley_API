#pragma once

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

	double getDeltaTime();
	float getFPS();

public:

	Timer();
	void Update();
	void UpdateFPS();

	

};