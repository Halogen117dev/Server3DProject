#include "OGLCanvas.h"

int counter = 0;

OGLCanvas::OGLCanvas(MainFrame* parent, const wxGLAttributes& canvasAttrs)
    : wxGLCanvas(parent, canvasAttrs)
{
    //Other Stuff
    BGColor.r = 0.0f;
    BGColor.g = 0.0f;
    BGColor.b = 0.0f;

    Height = this->GetSize().x;
    Width = this->GetSize().y;

    MyTimer = new Timer();
    //Other Stuff

    ParentCurlHandler = parent->MyCurlHandler;
    Input = new InputManager(this);

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
    MyGame = nullptr;


    Bind(wxEVT_PAINT, &OGLCanvas::OnPaint, this);
    Bind(wxEVT_IDLE, &OGLCanvas::OnIdle, this);
    Bind(wxEVT_SIZE, &OGLCanvas::OnSize, this);
}

OGLCanvas::~OGLCanvas()
{
    delete OGLContext;
    delete MyGPU;
    delete MyGame;
    delete MyTimer;
    delete Input;
}


void OGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    bool firstAppearance = IsShownOnScreen() && !MyGPU->GetOGLInitStatus();
    
    //SETCURRENT DOES NOT WORK HERE FOR SOME REASON
    //SO IT IS PUT IN ONSIZE() METHOD
    std::vector<CurlHandler::WorkstationState> workstations;
    if (ParentCurlHandler)
    {
        workstations = ParentCurlHandler->RequestWorkstations();
    }

    BGColor.r = 0.55f;
    BGColor.g = 0.55f;
    BGColor.b = 0.65f;

    //std::stringstream sstream;
    //sstream << ParentCurlHandler->ElapsedTimeSinceRequest << "   " << ParentCurlHandler->CurlTimer.DebugGetDT();
    //wxLogLastError(sstream.str());


    int dt = MyTimer->DT();
    int t = MyTimer->GetTime();
    
    //MyGame->Update will be called even when the game isn't even made yet!
    //FOUND THIS THROUGH THE OBJLoader's FILE.is_open THING
    if (MyGame != nullptr)
    {
        MyGame->Update(t, dt, workstations);
        MyGPU->SetBGColor(BGColor);
        MyGPU->Render(MyGame->GetCamera(), MyGame->GetMainNode());
    }
    
    SwapBuffers();
}


//WORKS FOR NEW IMPLEMENTATION TOO!
void OGLCanvas::OnIdle(wxIdleEvent& event)
{
    wxPoint mousePos = ScreenToClient(wxGetMousePosition());
    if ((mousePos.x > 0) && (mousePos.x < Width))
    {
        if ((mousePos.y > 0) && (mousePos.y < Height))
        {
            Input->SetMouseInClient(true);
        }
        else
        {
            Input->SetMouseInClient(false);
        }
    }
    else
    {
        Input->SetMouseInClient(false);
    }
    //std::string out = std::to_string(counter++);
    //out.push_back('\n');
    //OutputDebugStringA(out.c_str());
    
    Input->Update(event);
    Refresh();

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
        MyGame = new GameManager(Input);
    }

    if (MyGPU->GetOGLInitStatus())
    {
        auto viewPortSize = event.GetSize();
        glViewport(0, 0, viewPortSize.x, viewPortSize.y);
        Height = viewPortSize.y;
        Width = viewPortSize.x;
        MyGame->GetCamera()->SetAspectRatio(static_cast<float>(Width) / Height);
    }

    event.Skip();
}

wxSize OGLCanvas::GetDimensions()
{
    return wxSize(Width, Height);
}
