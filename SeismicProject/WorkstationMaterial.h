#pragma once
#include "Material.h"
class WorkstationMaterial : public Material
{
public:
	WorkstationMaterial();
	~WorkstationMaterial();

	// Takes two inputs and updates the uniforms accordingly.
	// Server status is inferred as 1->Powered Off, 2->Powered On with No Users (Offline),
	// 3->Powered On with Users (Online)
	// Time is in milliseconds.
	void UpdateStatus(GLuint serverStatus, GLuint timeMS);

	void SetTexture(const char* texturePath, GLint internalFormat = GL_RGB, GLenum externalFormat = GL_RGB);

private:
	GLuint
		ServerStatus,
		Time,
		DT;

protected:
	virtual void ReadyShader() override;
};

