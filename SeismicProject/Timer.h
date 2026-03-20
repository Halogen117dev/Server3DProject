#include<chrono>

#pragma once
class Timer
{
public:
	Timer();
	int DT();

private:
	std::chrono::steady_clock::time_point PresentTime;
	std::chrono::steady_clock::time_point PreviousTime;
	int DeltaTime = 0;
};

