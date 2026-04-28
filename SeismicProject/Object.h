#pragma once
#include "Node.h"

class Object : public Node
{
public:
	Object(
		GameManager* game,
		const char* name,
		const char* modelPath 
	);
	~Object();

	void Update() override;
	void CustomUpdate() override;

	void Render(
		std::shared_ptr<Camera> camera,
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)
	) override;

	void AttachModel();
	void AttachModel(const char* modelPath);

	void SetTransform(
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)
	);

	void Transform(
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)
	);

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 sca);

	void Translate(glm::vec3 translationVal);
	void Rotate(glm::vec3 rotationVal);
	void ScaleMult(glm::vec3 scaleVal);

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

