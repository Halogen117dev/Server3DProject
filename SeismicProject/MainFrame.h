#pragma once
#include<wx/wx.h>

#include"CurlHandler.h"

class OGLCanvas;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
    ~MainFrame();
    CurlHandler* MyCurlHandler;
private:
    OGLCanvas* openGLCanvas{ nullptr };
};

