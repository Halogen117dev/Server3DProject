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

	unsigned int GetHandle();
	bool AttachAndLink();

private:
	unsigned int Handle;
	std::vector<std::shared_ptr<DefaultShader>> Shaders;
};

