#include<chrono>

#pragma once
class Timer
{
public:
	Timer();
	int DT();

private:
	std::chrono::high_resolution_clock::time_point PresentTime;
	std::chrono::high_resolution_clock::time_point PreviousTime;
	int DeltaTime = 0;

public:
	int DebugGetDT();
};

