#include<curl/curl.h>
#include"Timer.h"

#include<vector>

#pragma once
class CurlHandler
{
public:
	CurlHandler(const char* curlURL);
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


	struct Service
	{
		std::string Name;
		std::string Status;
	};
	struct ServerState
	{
		float CpuUsage = 0.0f;
		std::string Model;
		std::string Name;
		bool PowerState = false;	//FALSE IS OFF/TRUE IS ON
		float RamUsage = 0.0f;
		std::vector<Service> Services;

		bool UnknownStatus = false;
	};

private:
	CURL* MyCurl = nullptr;
	std::string MyURL;

	std::vector<WorkstationState> MyWorkstations;
	std::vector<ServerState> MyServers;

public:
	Timer WorkstationTimer, ServerTimer;

	std::vector<WorkstationState> RequestWorkstations();
	std::vector<WorkstationState> GetWorkstations();

	std::vector<ServerState> RequestServers();
	std::vector<ServerState> GetServers();


	unsigned long ElapsedTimeSinceWorkstationRequest;
	unsigned long ElapsedTimeSinceServerRequest;
};

