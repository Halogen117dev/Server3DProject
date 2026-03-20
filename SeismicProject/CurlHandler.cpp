#include "CurlHandler.h"
#include<string>
#include<glaze/glaze.hpp>

#include<exception>

CurlHandler::CurlHandler(const char* CurlURL)
{
	MyCurl = curl_easy_init();
	
	if (MyCurl == NULL)
	{
		throw 123;
	}

	//curl_easy_setopt(MyCurl, CURLOPT_URL, CurlURL);
}

// Callback function to handle the data returned by the server
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

// Helper struct for parsing JSON
struct Health
{
	std::string status;
	std::string version;
};

void CurlHandler::RequestHealth()
{

	curl_easy_setopt(MyCurl, CURLOPT_URL, "http://127.0.0.1:5000/api/v1/health");

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
		UnknownStatus = false;
		IsUp = true;
	}
	else if (h.status == "down")
	{
		UnknownStatus = false;
		IsUp = false;
	}
	else
	{
		UnknownStatus = true;
	}
	
}

void CurlHandler::RequestStatus()
{
}
