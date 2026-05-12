#include "ShaderProgram.h"

#include<vector>

ShaderProgram::ShaderProgram()
{
	Handle = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	//do anything
}

void ShaderProgram::AddShader(std::shared_ptr<DefaultShader> shader)
{
	Shaders.push_back(shader);
}

GLuint ShaderProgram::GetHandle()
{
	return Handle;
}

void ShaderProgram::AttachAndLink()
{
	for (int i = 0; i < Shaders.size(); i++)
	{
		glAttachShader(Handle, Shaders[i]->GetHandle());
	}
	glLinkProgram(Handle);

	GLint success;
	GLchar infoLog[2048];
	glGetProgramiv(Handle, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Handle, 1024, nullptr, infoLog);
		throw(DefaultShader::ShaderException(infoLog));
	}

	for (int i = 0; i < Shaders.size(); i++)
	{
		glDetachShader(Handle, Shaders[i]->GetHandle());
	}
}
