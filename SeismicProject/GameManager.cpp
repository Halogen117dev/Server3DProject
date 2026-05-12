#include "GameManager.h"


GameManager::GameManager(InputManager* input)
{
	dt = 1;
	t = 1;
	//MAIN NODE IS NEVER IN NODEMAP
	MainNode = std::make_shared<Node>(this, "MainNode");
	//MAIN NODE IS NEVER IN NODEMAP

	Input = input;


	std::shared_ptr<Object> obj1 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "ws-1", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj2 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "ws-2", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj3 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "ws-3", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj4 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "ws-4", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj5 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "ws-5", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj6 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "ws-6", "resources/models/HP_Z8.obj")));

	std::shared_ptr<Object> mon1 = std::dynamic_pointer_cast<Object>(std::make_shared<Object>(this, "ws-1", "resources/models/Monitor.obj"));
	std::shared_ptr<Object> mon2 = std::dynamic_pointer_cast<Object>(std::make_shared<Object>(this, "ws-2", "resources/models/Monitor.obj"));
	std::shared_ptr<Object> mon3 = std::dynamic_pointer_cast<Object>(std::make_shared<Object>(this, "ws-3", "resources/models/Monitor.obj"));
	std::shared_ptr<Object> mon4 = std::dynamic_pointer_cast<Object>(std::make_shared<Object>(this, "ws-4", "resources/models/Monitor.obj"));
	std::shared_ptr<Object> mon5 = std::dynamic_pointer_cast<Object>(std::make_shared<Object>(this, "ws-5", "resources/models/Monitor.obj"));
	std::shared_ptr<Object> mon6 = std::dynamic_pointer_cast<Object>(std::make_shared<Object>(this, "ws-6", "resources/models/Monitor.obj"));

	obj1->AddChild(mon1);
	mon1->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	mon1->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));

	obj2->AddChild(mon2);
	mon2->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	mon2->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));

	obj3->AddChild(mon3);
	mon3->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	mon3->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));

	obj4->AddChild(mon4);
	mon4->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	mon4->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));

	obj5->AddChild(mon5);
	mon5->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	mon5->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));

	obj6->AddChild(mon6);
	mon6->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	mon6->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));

	std::shared_ptr<Object> floor = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj5", "resources/models/floor.obj")));

	floor->Translate(glm::vec3(-2.0f, -0.0f, -2.0f));
	floor->Rotate(glm::vec3(0.0f, 0.0f, 0.0f));
	
	try
	{
		std::shared_ptr<Material> floorMat = std::make_shared<FloorMaterial>();
		floor->AttachMaterial(floorMat);
	}
	catch (DefaultShader::ShaderException &e)
	{
		OutputDebugStringA(e.what());
		OutputDebugStringA("MAJOR\nMAJOR\nMAJOR\nMAJOR\nMAJOR\nMAJORFUCKUP!!!");
	}

	
	obj1->Translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	obj2->Translate(glm::vec3(-2.0f, 0.0f, -2.0f));
	obj3->Translate(glm::vec3(-4.0f, 0.0f, 0.0f));
	obj4->Translate(glm::vec3(-4.0f, 0.0f, -2.0f));
	obj5->Translate(glm::vec3(-4.0f, 0.0f, -4.0f));

	MainCamera = std::make_shared<Camera>(this);
}

GameManager::~GameManager()
{
}

void GameManager::Update(int time, int deltaTime, std::vector<CurlHandler::WorkstationState> workstations)
{	
	MainCamera->Update();

	t = time;
	dt = deltaTime;
	Workstations = workstations;

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

