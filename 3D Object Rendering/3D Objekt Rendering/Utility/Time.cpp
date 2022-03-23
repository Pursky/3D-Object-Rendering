#include "Time.h"

Time::Time()
{
	lastTime = high_resolution_clock::now();
	DeltaTime = 0;
}

void Time::Update()
{
	high_resolution_clock::time_point now = high_resolution_clock::now();

	duration<float> delta = now - lastTime;
	DeltaTime = delta.count();

	lastTime = now;
}