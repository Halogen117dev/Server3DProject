#include "GameManager.h"


GameManager::GameManager()
{
	ModelList.push_back(std::make_shared<Model>());
	MainCamera = std::make_shared<Camera>();
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{

}

std::vector<std::shared_ptr<Model>>& GameManager::GetModelList()
{
	return ModelList;
}

std::shared_ptr<Camera>& GameManager::GetCamera()
{
	return MainCamera;
}
