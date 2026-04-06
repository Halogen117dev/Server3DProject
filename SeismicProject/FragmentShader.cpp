#include "FragmentShader.h"

FragmentShader::FragmentShader()
{
	Handle = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentSource = get_file_contents("Fragment.frag");
	const char* fragmentCode = fragmentSource.c_str();

	glShaderSource(Handle, 1, &fragmentCode, nullptr);
	glCompileShader(Handle);
}

