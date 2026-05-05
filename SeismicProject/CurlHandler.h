#include<curl/curl.h>
#include"Timer.h"

#include<vector>

#pragma once
class CurlHandler
{
public:
	CurlHandler(const char* CurlURL);
	~CurlHandler();


	struct WorkstationState
	{
		std::string HostName;
		std::string IP;
		std::string LastSeen;
		std::string OS;
		bool PowerState = false;	//FALSE IS OFF/TRUE IS ON
		std::string Room;
		bool Status = false;		//FALSE IS OFFLINE/TRUE IS ONLINE
	};

private:
	CURL* MyCurl = nullptr;
	WorkstationState MyWorkstationState;

	std::vector<WorkstationState> MyWorkstations;
	//Timer CurlTimer;

public:
	Timer CurlTimer;

	std::vector<WorkstationState> RequestWorkstations();
	std::vector<WorkstationState> GetWorkstations();


	int ElapsedTimeSinceRequest = 0;
};

