#pragma once
//#include<wx/wx.h>
//#include<glad/glad.h> //must be included before glcanvas.h
//#include<wx/glcanvas.h>

#include"GPUManager.h"
#include"CurlHandler.h"
#include"MainFrame.h"

class OGLCanvas : public wxGLCanvas
{
public:
    OGLCanvas(MainFrame* parent, const wxGLAttributes& canvasAttrs);
    ~OGLCanvas();

    bool InitOpenGLFunctions();
    bool InitOpenGL();

    void OnPaint(wxPaintEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnSize(wxSizeEvent& event);

    CurlHandler* ParentCurlHandler;
private:
    float r = 0.0f, g = 0.0f, b = 0.0f;
    bool IsOpenGLInitialized{ false };

    unsigned int VAO, VBO, ShaderProgram;

    wxGLContext* OGLContext;
    GPUManager* MyGPU;
};

