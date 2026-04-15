#pragma once
#include "Node.h"

class Object : public Node
{
public:
	Object(
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)
	);
	~Object();

	void Render(
		std::shared_ptr<Camera> camera,
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)
	) override;

	void AttachModel();

private:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

private:
	//Each object may have a singular instance of a model.
	//unique_ptr is used, as only its parent Object may
	//access its render() method. Or something, I don't 
	//really know at all.
	std::unique_ptr<Model> MyModel;
};

