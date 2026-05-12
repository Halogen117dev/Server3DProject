#pragma once
#include<glad/glad.h>

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<string>
#include<exception>

class DefaultShader
{
public:
	class ShaderException : public std::exception
	{
	public:
		ShaderException(const char* message) noexcept
		{
			Message = message;
		}

		const char* what() const noexcept override
		{
			return Message.c_str();
		}
	private:
		std::string Message;
	};


public:
	DefaultShader();
	~DefaultShader();

	GLuint GetHandle();
protected:
	GLuint Handle;

	//HELPER FOR READING OF SHADER FILES
	std::string get_file_contents(const char* filename);

	void CheckShaderCompilation();
};

