#pragma once
#include"VertexShader.h"
#include"FragmentShader.h"

#include<vector>
#include<string>
#include<memory>
#include<exception>

class ShaderProgram
{
public:


public:
	ShaderProgram();
	~ShaderProgram();

	//CHANGE REMINDER
	//Currently, this function takes a shared_ptr to a shader, this must be
	//changed to taking a const char* to a filename containing a shader.
	//This will allow us to change the Shaders vector from shared_ptr to a
	//unique_ptr, increasing performance by 0.1ms because that's just sooo
	//significant, isn't it?
	void AddShader(std::shared_ptr<DefaultShader> shader);

	GLuint GetHandle();
	bool AttachAndLink();

private:
	GLuint Handle;

	//Look to reminder of AddShader().
	std::vector<std::shared_ptr<DefaultShader>> Shaders;
};

