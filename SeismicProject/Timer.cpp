#include "Timer.h"
#include<iostream>

Timer::Timer()
{
	PresentTime = std::chrono::steady_clock::now();
	PreviousTime = std::chrono::steady_clock::now();
}

int Timer::DT()
{
	PresentTime = std::chrono::steady_clock::now();
	DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(PresentTime - PreviousTime).count();
	PreviousTime = PresentTime;

	return DeltaTime;
}
