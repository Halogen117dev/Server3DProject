#pragma once
#include<wx/wx.h>
#include<glad/glad.h>
#include<wx/glcanvas.h>

#include<vector>
#include<memory>

#include "Node.h"
#include"Object.h"

class GPUManager
{
public:
	GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas);
	~GPUManager();

	bool InitOGLFunctions();
	bool InitOGL();

	bool Render(std::shared_ptr<Camera> camera, std::shared_ptr<Node> mainNode);

	void SetBGColor(glm::vec3 bgColor);

	bool GetOGLInitStatus();

private:
	wxGLCanvas* ParentGLCanvas;
	wxGLContext* OGLContext;
	bool IsOGLInitialized{ false };

	//Gone to the GameManager now lol
	//std::vector<std::shared_ptr<Model>> ModelList;
private:
	glm::vec4 BGColor;

	GLuint FBO;
	GLuint RBO;
    GLuint FramebufferTexture;

	GLuint RectVAO, RectVBO;

	std::unique_ptr<ShaderProgram> FrameBufferShaderProgram;

public:
	void GenerateFBORBO(int width, int height);
};

