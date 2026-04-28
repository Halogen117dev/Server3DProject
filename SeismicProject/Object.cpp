#include "GameManager.h"



Object::Object(GameManager* game, const char* name, const char* modelPath)
	: Node(game, name)
{
	ID = name;
	Type = Node::NodeType::OBJECT;
	
	SetTransform();

	AttachModel(modelPath);
}

Object::~Object()
{
}

void Object::Update()
{
	CustomUpdate();

	//do update stuff
	for (int i = 0; i < ChildrenList.size(); i++)
	{
		ChildrenList[i]->Update();
	}
}

void Object::CustomUpdate()
{
	GLuint serverStatus;
	if (Game->ServerState().UnknownStatus)
	{
		serverStatus = 0;
	}
	else
	{
		if (Game->ServerState().IsUp)
			serverStatus = 1;
		else
			serverStatus = 2;
	}
	MyModel->serverStatus = serverStatus;
	MyModel->time = Game->Time();
}

void Object::Render(std::shared_ptr<Camera> camera, glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	glm::vec3 finalPos = Position + pos;
	glm::vec3 finalRot = Rotation + rot;
	glm::vec3 finalSca = Scale * sca;

	if (MyModel)
		MyModel->Render(camera, finalPos, finalRot, finalSca);

	for (int i = 0; i < ChildrenList.size(); i++)
	{
		ChildrenList[i]->Render(camera, finalPos, finalRot, finalSca);
	}
}

void Object::AttachModel()
{
	MyModel = std::make_unique<Model>();
}

void Object::AttachModel(const char* modelPath)
{
	MyModel = std::make_unique<Model>(modelPath);
}

void Object::SetTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	Position = pos;
	Rotation = rot;
	Scale = sca;
}

void Object::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	Position += pos;
	Rotation += rot;
	Scale *= sca;
}

void Object::SetPosition(glm::vec3 pos)
{
	Position = pos;
}

void Object::SetRotation(glm::vec3 rot)
{
	Rotation = rot;
}

void Object::SetScale(glm::vec3 sca)
{
	Scale = sca;
}

void Object::Translate(glm::vec3 translationVal)
{
	Position += translationVal;
}

void Object::Rotate(glm::vec3 rotationVal)
{
	Rotation += rotationVal;
}

void Object::ScaleMult(glm::vec3 scaleVal)
{
	Scale *= scaleVal;
}
