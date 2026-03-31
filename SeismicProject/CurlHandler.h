#include<curl/curl.h>
#include"Timer.h"


#pragma once
class CurlHandler
{
public:
	CurlHandler(const char* CurlURL);
	~CurlHandler();

	struct ServerState
	{
		bool IsUp = false;
		bool UnknownStatus = true;
	};

private:
	CURL* MyCurl = nullptr;
	ServerState MyServerState;
	//Timer CurlTimer;

public:
	Timer CurlTimer;
	
	ServerState RequestServerState();
	ServerState GetServerState();
	int ElapsedTimeSinceRequest = 0;
};

