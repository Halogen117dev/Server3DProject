#include "CurlHandler.h"
#include<string>
#include<glaze/glaze.hpp>

CurlHandler::CurlHandler(const char* CurlURL)
{
	MyCurl = curl_easy_init();

	if (MyCurl == nullptr)
	{
		throw 123;
	}

	curl_easy_setopt(MyCurl, CURLOPT_URL, CurlURL);
}

CurlHandler::~CurlHandler()
{
	curl_easy_cleanup(MyCurl);
	//delete MyCurl;
}



// Callback function to handle the data returned by the server
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) 
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

// Helper struct for parsing JSON
struct Health
{
	std::string status;
	std::string version;
};


CurlHandler::ServerState CurlHandler::RequestServerState()
{
	if (ElapsedTimeSinceRequest > 1000000) //in microseconds
	{
		//curl_easy_setopt(MyCurl, CURLOPT_URL, "http://127.0.0.1:5000/api/v1/health");

		std::string readBuffer;

		// Provide the callback function to write the data
		curl_easy_setopt(MyCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(MyCurl, CURLOPT_WRITEDATA, &readBuffer);

		CURLcode res;
		res = curl_easy_perform(MyCurl);
		Health h{};
		glz::read_json<Health>(h, readBuffer);

		if (h.status == "up")
		{
			MyServerState.UnknownStatus = false;
			MyServerState.IsUp = true;
		}
		else if (h.status == "down")
		{
			MyServerState.UnknownStatus = false;
			MyServerState.IsUp = false;
		}
		else
		{
			MyServerState.UnknownStatus = true;
		}

		ElapsedTimeSinceRequest = 0;
	}

	ElapsedTimeSinceRequest += CurlTimer.DT();
	return MyServerState;
}

CurlHandler::ServerState CurlHandler::GetServerState()
{
	return MyServerState;
}
