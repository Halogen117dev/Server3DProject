#include "WorkstationMaterial.h"
#include "WorkstationMonitorObject.h"

WorkstationMaterial::WorkstationMaterial()
{
	ServerStatus = 0;
	Time = 0;
	DT = 0;

	MyShaderProgram.reset();
	MyShaderProgram = std::make_unique<ShaderProgram>();
	MyShaderProgram->AddShader(std::make_shared<VertexShader>("Vertex.vert"));
	MyShaderProgram->AddShader(std::make_shared<FragmentShader>("Workstation.frag"));
	MyShaderProgram->AttachAndLink();

	// +Textures must be cleared.
	Textures.clear();
	Textures.push_back(std::make_unique<Texture>("resources/images/HP_Z8_low_Export_Material_BaseColor_1k.png", GL_RGB, GL_RGB));
}

WorkstationMaterial::~WorkstationMaterial()
{
}

void WorkstationMaterial::UpdateStatus(GLuint serverStatus, GLuint timeMS)
{
	ServerStatus = serverStatus;
	Time = timeMS;
}

void WorkstationMaterial::SetTexture(const char* texturePath)
{
	Textures.clear();
	Textures.push_back(std::make_unique<Texture>(texturePath));
}

void WorkstationMaterial::ReadyShader()
{
	glUseProgram(MyShaderProgram->GetHandle());

	//TEXTURE UNIFORMS
	for (GLuint i = 0; i < Textures.size(); i++)
	{
		std::string textureName = "texture" + std::to_string(i);
		SetTextureUniform(i, textureName.c_str(), Textures[i]->GetHandle());
		//setTextureUniform(shaderProgram->GetHandle(), i, textureName.c_str(), Textures[i]->GetHandle());
	}

	SetUintUniform("serverStatus", ServerStatus);
	SetUintUniform("time", Time);
}


