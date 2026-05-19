#include "CurlHandler.h"
#include<iostream>
#include<nlohmann/json.hpp>


CurlHandler::CurlHandler(const char* curlURL)
{
	ElapsedTimeSinceServerRequest = 10000000;
	ElapsedTimeSinceWorkstationRequest = 10000000;

	MyCurl = curl_easy_init();

	if (MyCurl == nullptr)
	{
		throw 123;
	}
	MyURL = curlURL;
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



std::vector<CurlHandler::WorkstationState> CurlHandler::RequestWorkstations()
{
	if (ElapsedTimeSinceWorkstationRequest > 2000000) //in microseconds
	{
		std::string workstationURL = MyURL;
		workstationURL.append("workstations");
		CURLcode resSetopt = curl_easy_setopt(MyCurl, CURLOPT_URL, workstationURL.c_str());
		if (resSetopt != CURLE_OK)
			throw 123;

		std::string readBuffer;

		// Provide the callback function to write the data
		curl_easy_setopt(MyCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(MyCurl, CURLOPT_WRITEDATA, &readBuffer);

		CURLcode res;
		res = curl_easy_perform(MyCurl);
		if (res != CURLE_OK)
			throw 213;
		
		MyWorkstations.clear();
		nlohmann::json obj = nlohmann::json::parse(readBuffer);

		for (int i = 0; i < 99; i++)
		{
			std::string hostname	= obj[i]["hostname"];
			std::string ip			= obj[i]["ip"];
			std::string last_seen	= obj[i]["last_seen"];
			std::string os;
			if (obj[i]["os"] != nullptr)
				os = obj[i]["os"];
			else
				os = "Unavailable";
			std::string power_state = obj[i]["power_state"];
			std::string room		= obj[i]["room"];
			std::string status		= obj[i]["status"];

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

	ElapsedTimeSinceWorkstationRequest += WorkstationTimer.DT();
	return MyWorkstations;
}

std::vector<CurlHandler::WorkstationState> CurlHandler::GetWorkstations()
{
	return MyWorkstations;
}



std::vector<CurlHandler::ServerState> CurlHandler::RequestServers()
{
	if (ElapsedTimeSinceServerRequest > 10000000)	//in microseconds
	{
		std::string serverURL = MyURL;
		serverURL.append("servers");
		CURLcode resSetopt = curl_easy_setopt(MyCurl, CURLOPT_URL, serverURL.c_str());
		if (resSetopt != CURLE_OK)
			throw 123;

		std::string readBuffer;

		// Provide the callback function to write the data
		curl_easy_setopt(MyCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(MyCurl, CURLOPT_WRITEDATA, &readBuffer);

		CURLcode res;
		res = curl_easy_perform(MyCurl);
		if (res != CURLE_OK)
			throw 213;

		MyServers.clear();
		nlohmann::json objOG = nlohmann::json::parse(readBuffer);
		nlohmann::json obj = objOG.at("servers");

		for (int i = 0; i < 4; i++)
		{
			float cpu = obj[i]["cpu_usage"];
			std::string model = obj[i]["model"];
			std::string name = obj[i]["name"];
			std::string power = obj[i]["power_state"];
			float ram = obj[i]["ram_usage"];
			int numServices = obj[i].at("services").size();
			
			ServerState s;
			s.CpuUsage = cpu;
			s.Model = model;
			s.Name = name;
			if (power == "ON")
				s.PowerState = true;
			s.RamUsage = ram;

			if (numServices != 0)
			{
				nlohmann::json servicesObj = obj[i].at("services");
				for (int j = 0; j < numServices; j++)
				{
					Service service;
					service.Name = servicesObj[j]["name"];
					service.Status = servicesObj[j]["status"];
					s.Services.push_back(service);
				}
			}
		
			MyServers.push_back(s);
		}

		std::cout << obj << std::endl;

		ElapsedTimeSinceServerRequest = 0;
	}
	ElapsedTimeSinceServerRequest += ServerTimer.DT();
	return MyServers;
}

std::vector<CurlHandler::ServerState> CurlHandler::GetServers()
{
	return MyServers;
}
