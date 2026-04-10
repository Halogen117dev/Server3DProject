#pragma once

#include<memory>

#include"Mesh.h"
#include"Texture.h"
#include"ShaderProgram.h"

class Model
{
public:
	Model();
	~Model();

	
private:
	//THIS ALLOWS ONLY THE GPU MANAGER TO USE THE RENDER FUNCTION.
	//HOWEVER, PROBLEM ARISES AS GPU MANAGER CAN ALSO NOW ACCESS OTHER PRIVATE MEMBERS.
	friend class GPUManager;
	void Render();
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<std::unique_ptr<Texture>> Textures;
	std::vector<std::unique_ptr<Mesh>> Meshes;
};

