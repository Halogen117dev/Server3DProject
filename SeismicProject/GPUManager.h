#pragma once
#include<wx/wx.h>
#include<glad/glad.h>
#include<wx/glcanvas.h>

#include "ShaderProgram.h"

class GPUManager
{
public:
	GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas);
	~GPUManager();

	bool InitOGLFunctions();
	bool InitOGL();

	bool Render();

	void SetBGColor(float red, float green, float blue);

	bool GetOGLInitStatus();

private:
	wxGLCanvas* ParentGLCanvas;
	wxGLContext* OGLContext;
	bool IsOGLInitialized{ false };
	unsigned int
		VAO,
		VBO;
		//ShaderProgram;

	ShaderProgram* MyShaderProgram;

private:
	struct Color
	{
		float
			red,
			green,
			blue;
	};

	Color BGColor{ 1.0f, 1.0f, 1.0f };
};

