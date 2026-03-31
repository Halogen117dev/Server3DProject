#include "MainFrame.h"
#include "OGLCanvas.h"

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    MyCurlHandler = new CurlHandler("http://127.0.0.1:5000/api/v1/health");

    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();

    if (wxGLCanvas::IsDisplaySupported(vAttrs))
    {
        
        openGLCanvas = new OGLCanvas(this, vAttrs);
        //openGLCanvas->SetMinSize(wxSize(640, 800));
    }
    this->SetMinSize(wxSize(240, 144));
    //MyCurlHandler = new CurlHandler("http://127.0.0.1:5000/api/v1/health");

}

MainFrame::~MainFrame()
{
    delete MyCurlHandler;
    delete openGLCanvas;
}