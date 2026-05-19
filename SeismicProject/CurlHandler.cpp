#include "CurlHandler.h"
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>


CurlHandler::CurlHandler(const char* curlURL)
{
	MyCurl = curl_easy_init();

	if (MyCurl == nullptr)
	{
		throw 123;
	}

	CURLcode res = curl_easy_setopt(MyCurl, CURLOPT_URL, curlURL);
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


// Helper struct for parsing JSON for the WORKSTATIONS
struct Workstation
{
	std::string hostname;
	std::string ip;
	std::string last_seen;
	std::string os;
	std::string power_state;
	std::string room;
	std::string status;
};

std::vector<CurlHandler::WorkstationState> CurlHandler::RequestWorkstations()
{
	if (ElapsedTimeSinceWorkstationRequest > 1000000) //in microseconds
	{

		std::string readBuffer;

		// Provide the callback function to write the data
		curl_easy_setopt(MyCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(MyCurl, CURLOPT_WRITEDATA, &readBuffer);

		CURLcode res;
		res = curl_easy_perform(MyCurl);

		MyWorkstations.clear();
		nlohmann::json obj = nlohmann::json::parse(readBuffer);
		for (int i = 0; i < 99; i++)
		{
			std::string hostname = obj[i]["hostname"];
			std::string ip = obj[i]["ip"];
			std::string last_seen = obj[i]["last_seen"];
			std::string os;
			if (obj[i]["os"] != nullptr)
				os = obj[i]["os"];
			else
				os = "Unavailable";
			std::string power_state = obj[i]["power_state"];
			std::string room = obj[i]["room"];
			std::string status = obj[i]["status"];

			/*hostname = hostname.substr(1, hostname.size() - 2);
			ip = ip.substr(1, ip.size() - 2);
			last_seen = last_seen.substr(1, last_seen.size() - 2);
			if(os.size())
				os = os.substr(1, os.size() - 2);
			power_state = power_state.substr(1, power_state.size() - 2);
			room = room.substr(1, room.size() - 2);
			status = status.substr(1, status.size() - 2);*/

			WorkstationState w;
			w.HostName = hostname;
			w.IP = ip;
			w.LastSeen = last_seen;
			w.OS = os;
			if (power_state == "ON")
				w.PowerState = true;
			else
				w.PowerState = false;
			w.Room = room;
			if (status == "online")
				w.Status = true;
			else
				w.Status = false;

			MyWorkstations.push_back(w);
		}
		ElapsedTimeSinceWorkstationRequest = 0;
	}

	ElapsedTimeSinceWorkstationRequest += CurlTimer.DT();
	return MyWorkstations;
}

std::vector<CurlHandler::WorkstationState> CurlHandler::GetWorkstations()
{
	return MyWorkstations;
}
