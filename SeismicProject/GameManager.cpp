#include "GameManager.h"


GameManager::GameManager(InputManager* input)
{
	dt = 1;
	t = 1;
	//MAIN NODE IS NEVER IN NODEMAP
	MainNode = std::make_shared<Node>(this, "MainNode");
	//MAIN NODE IS NEVER IN NODEMAP

	Input = input;


	std::shared_ptr<Object> obj1 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<WorkstationObject>(this, "ws-1")));
	std::shared_ptr<Object> obj2 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<WorkstationObject>(this, "ws-2")));
	std::shared_ptr<Object> obj3 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<WorkstationObject>(this, "ws-3")));
	std::shared_ptr<Object> obj4 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<WorkstationObject>(this, "ws-4")));
	std::shared_ptr<Object> obj5 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<WorkstationObject>(this, "ws-5")));
	std::shared_ptr<Object> obj6 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<WorkstationObject>(this, "ws-6")));

	std::shared_ptr<Object> server1 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<ServerObject>(this, "server-1")));
	std::shared_ptr<Object> server2 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<ServerObject>(this, "server-2")));
	std::shared_ptr<Object> server3 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<ServerObject>(this, "server-3")));
	std::shared_ptr<Object> server4 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<ServerObject>(this, "server-4")));

	

	std::shared_ptr<Object> floor1 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Floor1", "resources/models/floor.obj")));
	std::shared_ptr<Object> floor2 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Floor2", "resources/models/floor.obj")));

	floor1->Translate(glm::vec3(-2.0f, -0.0f, -2.0f));
	floor1->Rotate(glm::vec3(0.0f, 0.0f, 0.0f));
	
	floor2->Translate(glm::vec3(-2.0f, -0.0f, 5.0f));
	floor2->Rotate(glm::vec3(0.0f, 180.0f, 0.0f));
	
	try
	{
		std::shared_ptr<Material> floorMat = std::make_shared<FloorMaterial>();
		floor1->AttachMaterial(floorMat);
		floor2->AttachMaterial(floorMat);
	}
	catch (DefaultShader::ShaderException &e)
	{
		OutputDebugStringA(e.what());
		OutputDebugStringA("MAJOR\nMAJOR\nMAJOR\nMAJOR\nMAJOR!!!");
	}

	
	obj1->Translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	obj2->Translate(glm::vec3(-2.0f, 0.0f, -2.0f));
	obj3->Translate(glm::vec3(-4.0f, 0.0f, 0.0f));
	obj4->Translate(glm::vec3(-4.0f, 0.0f, -2.0f));
	obj5->Translate(glm::vec3(-4.0f, 0.0f, -4.0f));

	server1->Transform(glm::vec3(-2.0f, 0.0f,  3.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.5f));
	server2->Transform(glm::vec3(-2.0f, 0.15f, 3.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.5f));
	server3->Transform(glm::vec3(-2.0f, 0.3f,  3.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.5f));
	server4->Transform(glm::vec3(-2.0f, 0.45f, 3.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.5f));


	MainCamera = std::make_shared<Camera>(this);
}

GameManager::~GameManager()
{
}

void GameManager::Update(
	int time, int deltaTime, 
	std::vector<CurlHandler::WorkstationState> workstations,
	std::vector<CurlHandler::ServerState> servers
	)
{	
	MainCamera->Update();

	t = time;
	dt = deltaTime;
	Workstations = workstations;
	Servers = servers;

	MainNode->Update();
}

std::shared_ptr<Node> GameManager::GetMainNode()
{
	return MainNode;
}

std::shared_ptr<Camera>& GameManager::GetCamera()
{
	return MainCamera;
}

std::shared_ptr<Node> GameManager::GetNodeFromMap(const char* id)
{
	if (NodeMap.contains(id))
	{
		return NodeMap.at(id);
	}
	else
	{
		return nullptr;
	}
}

void GameManager::AddNodeToMap(std::shared_ptr<Node> node)
{
	NodeMap[node->GetID()] = node;
}

GLuint GameManager::Time()
{
	return t;
}

GLuint GameManager::DeltaTime()
{
	return dt;
}

CurlHandler::WorkstationState GameManager::GetWorkstationState(const char* hostname)
{
	for (int i = 0; i < Workstations.size(); i++)
	{
		if (Workstations[i].HostName == hostname)
		{
			CurlHandler::WorkstationState w;
			w.HostName = Workstations[i].HostName;
			w.IP = Workstations[i].IP;
			w.LastSeen = Workstations[i].LastSeen;
			w.OS = Workstations[i].OS;
			w.PowerState = Workstations[i].PowerState;
			w.Room = Workstations[i].Room;
			w.Status = Workstations[i].Status;

			return w;
		}
	}

	CurlHandler::WorkstationState w;
	w.HostName = "NOT FOUND!";
	w.PowerState = false;
	w.Status = false;
	return w;
}

CurlHandler::ServerState GameManager::GetServerState(const char* hostname)
{
	for (int i = 0; i < Servers.size(); i++)
	{
		if (Servers[i].Name == hostname)
		{
			CurlHandler::ServerState s;
			s.CpuUsage = Servers[i].CpuUsage;
			s.Model = Servers[i].Model;
			s.Name = Servers[i].Name;
			s.PowerState = Servers[i].PowerState;
			s.RamUsage = Servers[i].RamUsage;
			s.Services = Servers[i].Services;
			return s;
		}		
	}
	CurlHandler::ServerState s;
	s.Name = "NOT FOUND!";
	s.Model = "NOT FOUND";
	s.UnknownStatus = true;
	return s;
}

