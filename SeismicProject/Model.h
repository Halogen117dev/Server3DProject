#pragma once

#include<memory>
#include<stb_image.h>

#include"Mesh.h"
#include"ShaderProgram.h"

class Model
{
public:
	Model();
	~Model();

	void Render();
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<std::unique_ptr<Mesh>> Meshes;
};

