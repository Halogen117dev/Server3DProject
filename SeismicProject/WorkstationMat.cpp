#include "WorkstationMat.h"

WorkstationMat::WorkstationMat()
{
	MyShaderProgram.reset();
	MyShaderProgram = std::make_unique<ShaderProgram>();
	MyShaderProgram->AddShader(std::make_shared<VertexShader>("Vertex.vert"));
	MyShaderProgram->AddShader(std::make_shared<FragmentShader>("Workstation.frag"));

}

WorkstationMat::~WorkstationMat()
{
}
