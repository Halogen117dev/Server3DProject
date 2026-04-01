#include "OGLCanvas.h"


OGLCanvas::OGLCanvas(MainFrame* parent, const wxGLAttributes& canvasAttrs)
    : wxGLCanvas(parent, canvasAttrs)
{
    ParentCurlHandler = parent->MyCurlHandler;

    wxGLContextAttrs ctxAttrs;
    ctxAttrs.PlatformDefaults().CoreProfile().OGLVersion(4, 6).EndList();
    OGLContext = new wxGLContext(this, nullptr, &ctxAttrs);

    if (!OGLContext->IsOK())
    {
        wxMessageBox(
            "This sample needs an OpenGL 4.6 capable driver.",
            "OpenGL Version Error!",
            wxOK | wxICON_INFORMATION, this);
        delete OGLContext;
        OGLContext = nullptr;
    }

    //GPUManager NEW STUFF
    //WARNING haven't checked if OGLContext exists or not!
    MyGPU = new GPUManager(OGLContext, this);


    Bind(wxEVT_PAINT, &OGLCanvas::OnPaint, this);
    Bind(wxEVT_IDLE, &OGLCanvas::OnIdle, this);
    Bind(wxEVT_SIZE, &OGLCanvas::OnSize, this);
}

OGLCanvas::~OGLCanvas()
{
    delete OGLContext;
    delete MyGPU;
}


void OGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    bool firstAppearance = IsShownOnScreen() && !MyGPU->GetOGLInitStatus();
    
    //SETCURRENT DOES NOT WORK HERE FOR SOME REASON
    //SO IT IS PUT IN ONSIZE() METHOD
    
    if (ParentCurlHandler)
    {
        CurlHandler::ServerState serverState = ParentCurlHandler->RequestServerState();

        if (serverState.UnknownStatus)
        {
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
        }
        else
        {
            if (serverState.IsUp)
            {
                r = 0.0f;
                g = 1.0f;
                b = 0.0f;
            }
            else if (!serverState.IsUp)
            {
                r = 1.0f;
                g = 0.0f;
                b = 0.0f;
            }
        }
    }
    else
    {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    //std::stringstream sstream;
    //sstream << ParentCurlHandler->ElapsedTimeSinceRequest << "   " << ParentCurlHandler->CurlTimer.DebugGetDT();
    //wxLogLastError(sstream.str());

    MyGPU->SetBGColor(r, g, b);

    MyGPU->Render();

    SwapBuffers();
}


//WORKS FOR NEW IMPLEMENTATION TOO!
void OGLCanvas::OnIdle(wxIdleEvent& event)
{
    Refresh();
    /*r += 0.0001;
    r = std::fmod(r, 1.0f);*/

    event.Skip();
}



void OGLCanvas::OnSize(wxSizeEvent& event)
{
    bool firstAppearance = IsShownOnScreen() && !MyGPU->GetOGLInitStatus();
    
    if (firstAppearance)
    {
        //SetCurrent() must be done before initializing OGL.
        //For some reason, a Render call is done as soon as initOGL returns. Maybe parallel execution?
        //Future work: ADD SETCURRENT CHECK IN RENDER/ONPAINT FUNCTION TO SKIP OGL STUFF
        SetCurrent(*OGLContext);
        MyGPU->InitOGL();
    }

    if (MyGPU->GetOGLInitStatus())
    {
        auto viewPortSize = event.GetSize();
        glViewport(0, 0, viewPortSize.x, viewPortSize.y);
    }

    event.Skip();
}