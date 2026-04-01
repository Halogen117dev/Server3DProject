#include "GPUManager.h"

GPUManager::GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas)
	: 
    OGLContext(openGLContext),
    ParentGLCanvas(parentGLCanvas)
{
}

GPUManager::~GPUManager()
{
}

bool GPUManager::InitOGLFunctions()
{
    GLenum version = gladLoadGL();
    if (version == 0)
    {
        wxMessageBox(
            "Failed to initialize GLAD",
            "OpenGL GLAD Error!",
            wxOK | wxICON_INFORMATION, ParentGLCanvas);

        return false;
    }
    return true;
}

bool GPUManager::InitOGL()
{
	if (!OGLContext)
		return false;

	//SetCurrent(*OGLContext);

    if (!InitOGLFunctions())
    {
        wxMessageBox(
            "Error: Could not initialize OpenGL function pointers.",
            "OpenGL Initialization Error",
            wxOK | wxICON_INFORMATION, ParentGLCanvas);

        return false;
    }

	wxLogDebug("OpenGL version: %s", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	wxLogDebug("OpenGL vendor: %s", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));


    int success;
    char infoLog[1024];

    MyShaderProgram = new ShaderProgram();
    MyShaderProgram->AttachAndLink();

    glGetProgramiv(MyShaderProgram->GetHandle(), GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(MyShaderProgram->GetHandle(), 1024, nullptr, infoLog);
        wxLogDebug("Shader Program Linking Failed: %s", infoLog);
    }

    

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

    IsOGLInitialized = true;

    return true;
}

bool GPUManager::Render()
{
    //wxLogDebug("TS RENDERIN");
    
    
    glClearColor(BGColor.red, BGColor.green, BGColor.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(MyShaderProgram->GetHandle());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return true;
}

void GPUManager::SetBGColor(float red, float green, float blue)
{
    BGColor.red = red;
    BGColor.green = green;
    BGColor.blue = blue;
}

bool GPUManager::GetOGLInitStatus()
{
    return IsOGLInitialized;
}
