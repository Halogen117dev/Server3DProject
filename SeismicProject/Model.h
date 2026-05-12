#pragma once

#include<memory>

#include"Camera.h"
#include"Mesh.h"
#include"Material.h"
#include"FloorMaterial.h"

class Model
{
public:
	//Model can be created by a user anywhere. But, rendering of model is restricted to the GPUManager.
	//Friend class given to GPUManager, so will have to be careful with what it can do. Or something, I guess bro.
	Model();	
	Model(const char* modelPath);
	~Model();

	//CHANGE IN RENDER METHOD - NOW IT IS PUBLIC!
	//RENDER CALLS FOR EVERYONE!
public:
	// DISREGARD BELOW COMMENTS, ONLY LEGACY NOSTALGIA
	//THIS ALLOWS ONLY THE GPU MANAGER TO USE THE RENDER FUNCTION.
	//HOWEVER, PROBLEM ARISES AS GPU MANAGER CAN ALSO NOW ACCESS OTHER PRIVATE MEMBERS.
	//friend class GPUManager;
	void Render(
		std::shared_ptr<Camera> camera, 
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)
	);

	void SetMaterial(std::shared_ptr<Material> material);
	
private:
	std::shared_ptr<Material> MyMaterial;
	std::vector<std::unique_ptr<Mesh>> Meshes;

private:
	glm::mat4 ModelMatrix;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	// TRANSFORMATIONS ONLY TO BE DONE WITHIN THE RENDER LOOP, WHEN THE MODEL MATRIX
	// HAS BEEN INITIALIZED TO IDENTITY MATRIX.
	void TransformMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);
	void TransformMatrix(glm::mat4 transformMatrix);

private:
	//Uniform setting functions
	void SetTextureUniform(
		GLuint textureNumber, 
		const char* uniformName, 
		GLuint textureHandle);

	void SetMat4Uniform(
		const char* uniformName,
		glm::mat4 matrix,
		GLboolean transpose = false
		);

	void SetVec3Uniform(
		const char* uniformName,
		glm::vec3 vector
	);
	
	void SetUintUniform(
		const char* uniformName,
		GLuint uint
	);
};

