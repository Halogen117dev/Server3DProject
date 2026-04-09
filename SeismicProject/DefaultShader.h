#pragma once
#include<glad/glad.h>

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

	unsigned int GetHandle();
protected:
	unsigned int Handle;

	//HELPER FOR READING OF SHADER FILES
	std::string get_file_contents(const char* filename);
};

