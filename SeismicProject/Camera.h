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
//WARNING

class Camera
{
public:
	Camera(float aspectRatio = static_cast<float>(4) / static_cast<float>(3), float fov = 80.0f, float near = 0.1f, float far = 1000.0f);
	~Camera();

private:
	//CAMERA PROPERTIES
	float FOV;
	float NearPlane;
	float FarPlane;
	float AspectRatio;

public:
	//GETTERS AND SETTERS
	//EACH SETTER HAS A CALL TO UPDATE PROJECTION MATRIX
	void SetFOV(float fov);
	float GetFOV();
	void SetNearPlane(float near);
	float GetNearPlane();
	void SetFarPlane(float far);
	float GetFarPlane();
	void SetAspectRatio(float aspectRatio);
	float GetAspectRatio();

private:
	//NEED TO ADD A SUBSTITUTE FOR MODEL MATRIX
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	void UpdateProjectionMatrix();

public:
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
};

