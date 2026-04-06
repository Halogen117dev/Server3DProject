#include "VertexShader.h"

VertexShader::VertexShader()
{	
	Handle = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexSource = get_file_contents("Vertex.vert");
	const char* vertexCode = vertexSource.c_str();

	glShaderSource(Handle, 1, &vertexCode, nullptr);
	glCompileShader(Handle);
}
