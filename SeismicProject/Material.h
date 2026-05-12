#pragma once
#include"ShaderProgram.h"
#include"Texture.h"

class Material
{
public:
	// Creates a default material using default fragment and vertex shaders,
	// and using a default texture. Other textures can extend this and make 
	// custom implementations.
	Material();
	~Material();

	//Sets uniforms and uses shader.
	virtual void ReadyShader();

protected:
	std::unique_ptr<ShaderProgram> MyShaderProgram;
	std::vector<std::unique_ptr<Texture>> Textures;

public:
	//Getter
	GLuint GetShaderProgramHandle();

	//Uniform setting functions

	// Sets texture uniform based on the texture vector.
	// Texture uniforms named based on numbers.
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

