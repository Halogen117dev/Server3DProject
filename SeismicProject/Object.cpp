#include "Object.h"

Object::Object(
	glm::vec3 pos = glm::vec3(0.0f),
	glm::vec3 rot = glm::vec3(0.0f),
	glm::vec3 sca = glm::vec3(1.0f)
)
	:
	Position(pos),
	Rotation(rot),
	Scale(sca)
{
	Type = Node::NodeType::OBJECT;
}

Object::~Object()
{
}

void Object::Render(std::shared_ptr<Camera> camera, glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	glm::vec3 finalPos = Position + pos;
	glm::vec3 finalRot = Rotation + rot;
	glm::vec3 finalSca = Scale + sca;

	if (MyModel)
		MyModel->Render(camera, finalPos, finalRot, finalSca);

	for (int i = 0; i < ChildrenList.size(); i++)
	{
		ChildrenList[i]->Render(camera, finalPos, finalRot, finalSca);
	}
}

void Object::AttachModel()
{
	if (!MyModel)
	{
		MyModel = std::make_unique<Model>();
	}
}
