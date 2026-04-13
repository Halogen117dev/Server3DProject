#pragma once

#include<memory>

#include"Mesh.h"
#include"Texture.h"
#include"ShaderProgram.h"

class Model
{
public:
	//Model can be created by a user anywhere. But, rendering of model is restricted to the GPUManager.
	//Friend class given to GPUManager, so will have to be careful with what it can do. Or something, I guess bro.
	Model();
	~Model();

	void Transform(
		glm::vec3 translation		= glm::vec3(0.0f),
		glm::vec3 scale				= glm::vec3(1.0f),
		glm::vec3 rotation			= glm::vec3(0.0f),
		glm::vec3 rotationOffset	= glm::vec3(0.0f)
	);

private:
	//THIS ALLOWS ONLY THE GPU MANAGER TO USE THE RENDER FUNCTION.
	//HOWEVER, PROBLEM ARISES AS GPU MANAGER CAN ALSO NOW ACCESS OTHER PRIVATE MEMBERS.
	friend class GPUManager;
	void Render();
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<std::unique_ptr<Texture>> Textures;
	std::vector<std::unique_ptr<Mesh>> Meshes;

private:
	glm::mat4 ModelMatrix;
	glm::mat4 TranslationMatrix;
	glm::mat4 RotationMatrix;
	glm::mat4 ScaleMatrix;	   
};

