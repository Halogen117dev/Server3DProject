#include "GPUManager.h"
#include "Model.h"

GPUManager::GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas)
	: 
    OGLContext(openGLContext),
    ParentGLCanvas(parentGLCanvas)
{
}

GPUManager::~GPUManager()
{
    delete(MyModel);
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

    MyModel = new Model();

    IsOGLInitialized = true;

    return true;
}


bool GPUManager::Render()
{
    //wxLogDebug("TS RENDERIN");
    
    
    glClearColor(BGColor.red, BGColor.green, BGColor.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    MyModel->Render();
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
