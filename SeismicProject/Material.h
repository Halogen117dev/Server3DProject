#pragma once
#include"ShaderProgram.h"
#include"Texture.h"

class Material
{
public:
	Material();
	~Material();

	virtual void ReadyShader();

protected:
	std::unique_ptr<ShaderProgram> MyShaderProgram;
	std::vector<std::unique_ptr<Texture>> Textures;

public:
	//Getter
	GLuint GetShaderProgramHandle();

	//Uniform setting functions
	void SetTextureUniform(
		GLuint textureNumber, 
		const char* uniformName, 
		GLuint textureHandle);

	void SetMat4Uniform(
		const char* uniformName,
		glm::mat4 matrix,
		GLboolean transpose = false
		);

	void SetVec3Uniform(
		const char* uniformName,
		glm::vec3 vector
	);
	
	void SetUintUniform(
		const char* uniformName,
		GLuint uint
	);
};

