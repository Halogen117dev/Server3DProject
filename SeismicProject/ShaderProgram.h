#pragma once
#include"VertexShader.h"
#include"FragmentShader.h"

#include<vector>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	unsigned int GetHandle();
	bool AttachAndLink();

private:
	unsigned int Handle;
	std::vector<DefaultShader*> Shaders;
};

