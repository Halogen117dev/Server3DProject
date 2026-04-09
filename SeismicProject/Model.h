#pragma once

#include<memory>

#include"Mesh.h"
#include"ShaderProgram.h"

class Model
{
public:
	Model();
	~Model();

	void Render();
private:
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<ShaderProgram> shaderProgram;
};

