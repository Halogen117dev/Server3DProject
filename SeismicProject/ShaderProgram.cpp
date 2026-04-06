#include "ShaderProgram.h"

#include<vector>

ShaderProgram::ShaderProgram()
{
	Handle = glCreateProgram();
	/*Shaders.push_back(new VertexShader());
	Shaders.push_back(new FragmentShader());*/
}

ShaderProgram::~ShaderProgram()
{
	/*for (int i = 0; i < Shaders.size(); i++)
	{
		delete(Shaders[i]);
	}*/
}

void ShaderProgram::AddShader(std::shared_ptr<DefaultShader> shader)
{
	Shaders.push_back(shader);
}

unsigned int ShaderProgram::GetHandle()
{
	return Handle;
}

bool ShaderProgram::AttachAndLink()
{
	for (int i = 0; i < Shaders.size(); i++)
	{
		glAttachShader(Handle, Shaders[i]->GetHandle());
	}
	glLinkProgram(Handle);

	for (int i = 0; i < Shaders.size(); i++)
	{
		glDetachShader(Handle, Shaders[i]->GetHandle());
	}

	return true;
}
