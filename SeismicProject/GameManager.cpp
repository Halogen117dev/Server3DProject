#include "GameManager.h"


GameManager::GameManager()
{
	MainNode = std::make_shared<Node>("MainNode");
	MainNode->AddChild(std::make_shared<Object>("Obj1"));
	MainNode->AddChild(std::make_shared<Object>("Obj2"));
	MainCamera = std::make_shared<Camera>();
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{	
	std::shared_ptr<Object> obj1 = std::dynamic_pointer_cast<Object>(MainNode->GetChildrenList()[0]);
	rotation1.y = 0.00001f;
	obj1->Transform(rotation1, glm::vec3(0.0f), glm::vec3(1.0f));

	std::shared_ptr<Object> obj2 = std::dynamic_pointer_cast<Object>(MainNode->GetChildrenList()[1]);
	rotation2.x = 0.00001f;
	obj2->Transform(rotation2, glm::vec3(0.0f), glm::vec3(1.0f));
}

std::shared_ptr<Node> GameManager::GetMainNode()
{
	return MainNode;
}

std::shared_ptr<Camera>& GameManager::GetCamera()
{
	return MainCamera;
}
