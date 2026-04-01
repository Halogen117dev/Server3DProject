#include "ShaderProgram.h"

#include<vector>

ShaderProgram::ShaderProgram()
{
	Handle = glCreateProgram();
	Shaders.push_back(new VertexShader());
	Shaders.push_back(new FragmentShader());
}

ShaderProgram::~ShaderProgram()
{

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

	Shaders.clear();

	return true;
}
