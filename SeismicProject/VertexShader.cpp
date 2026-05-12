#include "VertexShader.h"

VertexShader::VertexShader(const char* shaderSource)
{	
	Handle = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexSource = get_file_contents(shaderSource);
	const char* vertexCode = vertexSource.c_str();

	glShaderSource(Handle, 1, &vertexCode, nullptr);
	glCompileShader(Handle);
	CheckShaderCompilation();
}
