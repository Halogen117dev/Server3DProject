#include "MainFrame.h"
#include "OGLCanvas.h"

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    MyCurlHandler = new CurlHandler("http://192.168.1.101:5001/api/workstations");

    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();
    this->SetSize(1920, 1080);
    if (wxGLCanvas::IsDisplaySupported(vAttrs))
    {
        
        openGLCanvas = new OGLCanvas(this, vAttrs);
        //openGLCanvas->SetMinSize(wxSize(640, 800));
    }
    this->SetMinSize(wxSize(240, 144));
}

MainFrame::~MainFrame()
{
    delete MyCurlHandler;
    delete openGLCanvas;
}