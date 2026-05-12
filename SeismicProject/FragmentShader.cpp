#include "FragmentShader.h"

FragmentShader::FragmentShader(const char* shaderSource)
{
	Handle = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentSource = get_file_contents(shaderSource);
	const char* fragmentCode = fragmentSource.c_str();

	glShaderSource(Handle, 1, &fragmentCode, nullptr);
	glCompileShader(Handle);
	CheckShaderCompilation();
}

