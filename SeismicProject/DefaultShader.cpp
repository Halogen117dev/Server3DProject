#include "DefaultShader.h"

#include<fstream>
#include<sstream>

DefaultShader::DefaultShader()
{
	Handle = 0;
}

DefaultShader::~DefaultShader()
{
	glDeleteShader(Handle);
}

GLuint DefaultShader::GetHandle()
{
	return Handle;
}

std::string DefaultShader::get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::in);
	if (in.good())
	{
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}
	//throw("Shader file not found!");
	return std::string("Shader file not found!");
}

void DefaultShader::CheckShaderCompilation()
{
	GLint success;
	GLchar infoLog[2048];
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Handle, 2048, nullptr,infoLog);
		throw(DefaultShader::ShaderException(infoLog));
	}
}
