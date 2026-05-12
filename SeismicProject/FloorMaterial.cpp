#include "FloorMaterial.h"

FloorMaterial::FloorMaterial()
{
	MyShaderProgram.reset();
	MyShaderProgram = std::make_unique<ShaderProgram>();
	MyShaderProgram->AddShader(std::make_shared<VertexShader>("Vertex.vert"));
	MyShaderProgram->AddShader(std::make_shared<FragmentShader>("Floor.Frag"));
	MyShaderProgram->AttachAndLink();
}

FloorMaterial::~FloorMaterial()
{

}

void FloorMaterial::ReadyShader()
{
    glUseProgram(MyShaderProgram->GetHandle());
}