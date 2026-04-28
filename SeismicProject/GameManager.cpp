#include "GameManager.h"


GameManager::GameManager(InputManager* input)
{
	//MAIN NODE IS NEVER IN NODEMAP
	MainNode = std::make_shared<Node>(this, "MainNode");
	//MAIN NODE IS NEVER IN NODEMAP

	Input = input;

	std::shared_ptr<Object> obj1 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj1", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj2 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj2", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj3 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj3", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj4 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj4", "resources/models/HP_Z8.obj")));
	std::shared_ptr<Object> obj5 = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj5", "resources/models/HP_Z8.obj")));

	std::shared_ptr<Object> floor = std::dynamic_pointer_cast<Object>(MainNode->AddChild(std::make_shared<Object>(this, "Obj5", "resources/models/floor.obj")));
	floor->Translate(glm::vec3(0.0f, -0.2f, 0.0f));

	MainCamera = std::make_shared<Camera>();
}

GameManager::~GameManager()
{
}

void GameManager::Update(int time, int deltaTime, CurlHandler::ServerState serverState)
{	
	t = time;
	dt = deltaTime;
	MyServerState = serverState;

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

CurlHandler::ServerState GameManager::ServerState()
{
	return MyServerState;
}
