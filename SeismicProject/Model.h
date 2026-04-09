#pragma once

#include<glm/glm.hpp>
#include<glm/vec2.hpp>

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

