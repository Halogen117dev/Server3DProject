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

	void AddShader(std::shared_ptr<DefaultShader> shader);

	GLuint GetHandle();
	bool AttachAndLink();

private:
	GLuint Handle;
	std::vector<std::shared_ptr<DefaultShader>> Shaders;
};

