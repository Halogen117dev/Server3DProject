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
