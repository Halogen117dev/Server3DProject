#include "App.h"
//#include"MainFrame.h"
#include<wx/wx.h>
#include<glad/glad.h> //must be included before glCanvas.h
#include<wx/glcanvas.h>
#include<math.h>

//networking
#include"CurlHandler.h"
#include"Timer.h"
#include<sstream>

float r  = 0.0f, g = 0.0f, b = 0.0f;


class OpenGLCanvas;

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    CurlHandler* MyCurlHandler;
private:
    OpenGLCanvas* openGLCanvas{ nullptr };
};

class OpenGLCanvas : public wxGLCanvas
{
public:
    OpenGLCanvas(MyFrame* parent, const wxGLAttributes& canvasAttrs);
    ~OpenGLCanvas();

    bool InitOpenGLFunctions();
    bool InitOpenGL();

    void OnPaint(wxPaintEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnSize(wxSizeEvent& event);

    CurlHandler* ParentCurlHandler;
private:
    wxGLContext* openGLContext;
    bool IsOpenGLInitialized{false};

    unsigned int VAO, VBO, ShaderProgram;
};


wxIMPLEMENT_APP(App);

//bool App::OnInit()
//{
//    MainFrame* mainFrame = new MainFrame("C++ GUI");
//    
//    //mainFrame->SetClientSize(2560/2, 1600/2);
//    mainFrame->Center();
//    mainFrame->Show();
//
//    return true;
//}

bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MyFrame* frame = new MyFrame("Hello OpenGL");
    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    MyCurlHandler = new CurlHandler("http://127.0.0.1:5000/api/v1/health");

    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();

    if (wxGLCanvas::IsDisplaySupported(vAttrs))
    {
        openGLCanvas = new OpenGLCanvas(this, vAttrs);
        openGLCanvas->SetMinSize(wxSize(640, 800));
    }

    //MyCurlHandler = new CurlHandler("http://127.0.0.1:5000/api/v1/health");
}

OpenGLCanvas::OpenGLCanvas(MyFrame* parent, const wxGLAttributes& canvasAttrs)
    : wxGLCanvas(parent, canvasAttrs)
{
    ParentCurlHandler = parent->MyCurlHandler;

    wxGLContextAttrs ctxAttrs;
    ctxAttrs.PlatformDefaults().CoreProfile().OGLVersion(4, 6).EndList();
    openGLContext = new wxGLContext(this, nullptr, &ctxAttrs);

    if (!openGLContext->IsOK())
    {
        wxMessageBox(
            "This sample needs an OpenGL 4.6 capable driver.",
            "OpenGL Version Error!",
            wxOK | wxICON_INFORMATION, this);
        delete openGLContext;
        openGLContext = nullptr;
    }

    Bind(wxEVT_PAINT, &OpenGLCanvas::OnPaint, this);
    Bind(wxEVT_IDLE, &OpenGLCanvas::OnIdle, this);
    Bind(wxEVT_SIZE, &OpenGLCanvas::OnSize, this);
}

OpenGLCanvas::~OpenGLCanvas()
{
    delete openGLContext;
}

bool OpenGLCanvas::InitOpenGLFunctions()
{
    GLenum version = gladLoadGL();
    if (version == 0)
    {
        wxMessageBox(
            "Failed to initialize GLAD",
            "OpenGL GLAD Error!",
            wxOK | wxICON_INFORMATION, this);

        return false;
    }

    //wxLogStatus("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    return true;
}

bool OpenGLCanvas::InitOpenGL()
{
    if (!openGLContext)
        return false;

    SetCurrent(*openGLContext);

    if (!InitOpenGLFunctions())
    {
        wxMessageBox(
            "Error: Could not initialize OpenGL function pointers.",
            "OpenGL Initialization Error",
            wxOK | wxICON_INFORMATION, this);
        
        return false;
    }

    wxLogDebug("OpenGL version: %s", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    wxLogDebug("OpenGL vendor: %s", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));

    constexpr auto vertexShaderSource = R"(
        #version 460 core
        layout (location = 0) in vec3 aPos;
        
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    constexpr auto fragmentShaderSource = R"(
        #version 460 core
        out vec4 FragColor;
        
        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);
        }
    )";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        wxLogDebug("Vertex Shader Compilation Failed: %s", infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        wxLogDebug("Fragment Shader Compilation Failed: %s", infoLog);
    }

    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(ShaderProgram, 512, nullptr, infoLog);
        wxLogDebug("Shader Program Linking Failed: %s", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[]
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    IsOpenGLInitialized = true;
    
    return true;
}


void OpenGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    
    SetCurrent(*openGLContext);

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

    /*std::stringstream sstream;
    sstream << ParentCurlHandler->ElapsedTimeSinceRequest << "   " << ParentCurlHandler->CurlTimer.DebugGetDT();
    wxLogLastError(sstream.str());*/
    

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(ShaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SwapBuffers();
}

void OpenGLCanvas::OnIdle(wxIdleEvent& event)
{
    Refresh();
    /*r += 0.0001;
    r = std::fmod(r, 1.0f);*/

    event.Skip();
}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{
    bool firstAppearance = IsShownOnScreen() && !IsOpenGLInitialized;

    if (firstAppearance)
    {
        InitOpenGL();
    }

    if (IsOpenGLInitialized)
    {
        auto viewPortSize = event.GetSize();
        glViewport(0, 0, viewPortSize.x, viewPortSize.y);
    }

    event.Skip();
}
