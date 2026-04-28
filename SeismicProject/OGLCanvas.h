#pragma once
//#include<wx/wx.h>
//#include<glad/glad.h> //must be included before glcanvas.h
//#include<wx/glcanvas.h>

#include"GPUManager.h"
#include"CurlHandler.h"
#include"MainFrame.h"
#include"GameManager.h"


class OGLCanvas : public wxGLCanvas
{
public:
    OGLCanvas(MainFrame* parent, const wxGLAttributes& canvasAttrs);
    ~OGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnSize(wxSizeEvent& event);
    
    CurlHandler* ParentCurlHandler;

    wxSize GetDimensions();
private:
    int
        Height,
        Width;

    glm::vec3 BGColor;

    wxGLContext* OGLContext;
    GameManager* MyGame;
    GPUManager* MyGPU;
    Timer* MyTimer;
    InputManager* Input;
};

