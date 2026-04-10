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

	void Render();
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<std::unique_ptr<Texture>> Textures;
	std::vector<std::unique_ptr<Mesh>> Meshes;
};

