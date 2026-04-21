#include "GameManager.h"


GameManager::GameManager()
{
	MainNode = std::make_shared<Node>("MainNode");
	MainNode->AddChild(std::make_shared<Object>("Obj1"));
	MainCamera = std::make_shared<Camera>();
}

GameManager::~GameManager()
{
}

void GameManager::Update(Input& input)
{	
	std::shared_ptr<Object> obj1 = std::dynamic_pointer_cast<Object>(MainNode->GetChildrenList()[0]);
	glm::vec3 translation(0.0f);
	if (input.IsKeyPressed("W"))
	{
		translation += glm::vec3(0.0f, 0.0f, -1.0f);
	}
	if (input.IsKeyPressed("A"))
	{
		translation += glm::vec3(-1.0f, 0.0f, 0.0f);
	}
	if (input.IsKeyPressed("S"))
	{
		translation += glm::vec3(0.0f, 0.0f, 1.0f);
	}
	if (input.IsKeyPressed("D"))
	{
		translation += glm::vec3(1.0f, 0.0f, 0.0f);
	}
	//translation = glm::normalize(translation);
	GLfloat speed = 0.001f;
	translation = glm::vec3(translation.x * speed, translation.y * speed, translation.z * speed);
	obj1->Translate(translation);

	glm::vec3 rotation(0.0f);
	if (input.IsKeyPressed("E"))
	{
		rotation += glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (input.IsKeyPressed("Q"))
	{
		rotation += glm::vec3(0.0f, -1.0f, 0.0f);
	}
	//translation = glm::normalize(translation);
	GLfloat rotSpeed = 0.02f;
	rotation = glm::vec3(rotation.x * rotSpeed, rotation.y * rotSpeed, rotation.z * rotSpeed);
	obj1->Rotate(rotation);
}

std::shared_ptr<Node> GameManager::GetMainNode()
{
	return MainNode;
}

std::shared_ptr<Camera>& GameManager::GetCamera()
{
	return MainCamera;
}
