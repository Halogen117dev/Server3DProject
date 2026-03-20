#include<curl/curl.h>
#include"Timer.h"


#pragma once
class CurlHandler
{
public:
	CurlHandler(const char* CurlURL);
	struct ServerState
	{
		bool IsUp = false;
		bool UnknownStatus = true;
	};

private:
	CURL* MyCurl = NULL;
	ServerState MyServerState;
	Timer CurlTimer;

public:
	ServerState RequestServerState();
	int ElapsedTimeSinceRequest = 0;
};

