#include "Timer.h"
#include<iostream>

Timer::Timer()
{
	PresentTime = std::chrono::high_resolution_clock::now();
	PreviousTime = std::chrono::high_resolution_clock::now();
}

int Timer::DT()
{
	PresentTime = std::chrono::high_resolution_clock::now();
	DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(PresentTime - PreviousTime).count();
	PreviousTime = PresentTime;

	return DeltaTime;
}

int Timer::DebugGetDT()
{
	return DeltaTime;
}
