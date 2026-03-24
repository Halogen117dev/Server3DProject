#include "OGLCanvas.h"


OGLCanvas::OGLCanvas(MainFrame* parent, const wxGLAttributes& canvasAttrs)
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

    VAO = VBO = ShaderProgram = 0;

    Bind(wxEVT_PAINT, &OGLCanvas::OnPaint, this);
    Bind(wxEVT_IDLE, &OGLCanvas::OnIdle, this);
    Bind(wxEVT_SIZE, &OGLCanvas::OnSize, this);
}

OGLCanvas::~OGLCanvas()
{
    delete openGLContext;
}


bool OGLCanvas::InitOpenGLFunctions()
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

bool OGLCanvas::InitOpenGL()
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


void OGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    bool firstAppearance = IsShownOnScreen() && !IsOpenGLInitialized;

    if (firstAppearance)
    {
        SetCurrent(*openGLContext);
    }

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

void OGLCanvas::OnIdle(wxIdleEvent& event)
{
    Refresh();
    /*r += 0.0001;
    r = std::fmod(r, 1.0f);*/

    event.Skip();
}

void OGLCanvas::OnSize(wxSizeEvent& event)
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
