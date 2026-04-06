#pragma once
#include<glad/glad.h>
#include<string>

class DefaultShader
{
public:
	DefaultShader();
	~DefaultShader();

	unsigned int GetHandle();
protected:
	unsigned int Handle;

	//HELPER FOR READING OF SHADER FILES
	std::string get_file_contents(const char* filename);
};

