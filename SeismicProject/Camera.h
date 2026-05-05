#pragma once

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


//WARNING
// EVERYTHING IN THIS CLASS IS IN STANDARD C++ FLOAT TYPES.
// I MUST CHANGE THESE LATER TO GL_FLOAT HOPEFULLY.
// OR NOT, I DON'T REALLY CARE.
// 
// I AM STUPID
// IT'S Glfloat, NOT GL_FLOAT
// OF COURSE IT WAS GIVING ME A DAMN ERROR, FUCK
// 
//WARNING

class GameManager;

class Camera
{
public:
	Camera(
		GameManager* game, 
		float aspectRatio = static_cast<float>(4) / static_cast<float>(3), 
		float fov = 60.0f, 
		float nearPlane = 0.1f, 
		float farPlane = 1000.0f);
	~Camera();

	void Update();

public:
	//TRANSFORMATIONS
	void SetTransform(
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f)
	);

	void Transform(
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f)
	);

	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition();
	void SetRotation(glm::vec3 rot);

	void Translate(glm::vec3 translationVal);
	void Rotate(glm::vec3 rotationVal);

private:
	//CAMERA PROPERTIES
	float FOV;
	float NearPlane;
	float FarPlane;
	float AspectRatio;

	float Speed;
	float Sensitivity;

	glm::vec3 Position;
	glm::vec3 Rotation;

	glm::vec3 Front;
	glm::vec3 Up;

public:
	//GETTERS AND SETTERS
	//EACH SETTER HAS A CALL TO UPDATE PROJECTION MATRIX
	void SetFOV(float fov);
	float GetFOV();
	void SetNearPlane(float nearPlane);
	float GetNearPlane();
	void SetFarPlane(float farPlane);
	float GetFarPlane();
	void SetAspectRatio(float aspectRatio);
	float GetAspectRatio();
	
private:
	//NEED TO ADD A SUBSTITUTE FOR MODEL MATRIX
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	void UpdateProjectionMatrix();
	void UpdateViewMatrix();


	GameManager* Game;
public:
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
};

