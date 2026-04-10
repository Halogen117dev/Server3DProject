#pragma once
#include<wx/wx.h>
#include<glad/glad.h>
#include<wx/glcanvas.h>

#include<vector>
#include<memory>

#include "Model.h"

class GPUManager
{
public:
	GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas);
	~GPUManager();

	bool InitOGLFunctions();
	bool InitOGL();

	bool Render();

	void SetBGColor(glm::vec3 bgColor);

	bool GetOGLInitStatus();

private:
	wxGLCanvas* ParentGLCanvas;
	wxGLContext* OGLContext;
	bool IsOGLInitialized{ false };

	std::vector<std::shared_ptr<Model>> ModelList;
private:
	glm::vec4 BGColor;
};

