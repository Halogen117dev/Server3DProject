#include<curl/curl.h>

#pragma once
class CurlHandler
{
public:
	CurlHandler(const char* CurlURL);

	void RequestHealth();
	void RequestStatus();
//private:

	bool IsUp = true;
	bool UnknownStatus = true;

private:
	CURL* MyCurl = NULL;
};

