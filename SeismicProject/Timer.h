#include<chrono>

#pragma once
class Timer
{
public:
	Timer();
	
	// Returns time delta in microseconds.
	int DT();

	// Returns current time since program start in milliseconds.
	int GetTime();

private:
	std::chrono::high_resolution_clock::time_point PresentTime;
	std::chrono::high_resolution_clock::time_point PreviousTime;
	int DeltaTime = 0;

public:
	int DebugGetDT();
};

