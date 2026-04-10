#include "GPUManager.h"
#include "Model.h"

GPUManager::GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas)
	: 
    OGLContext(openGLContext),
    ParentGLCanvas(parentGLCanvas)
{
    MyModel = nullptr;
    BGColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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

    //OPENGL Options
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return true;
}


bool GPUManager::Render()
{
    //wxLogDebug("TS RENDERIN");
    
    
    glClearColor(BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    

    MyModel->Render();
    return true;
}

void GPUManager::SetBGColor(glm::vec3 bgColor)
{
    BGColor = glm::vec4(bgColor, 1.0f);
}

bool GPUManager::GetOGLInitStatus()
{
    return IsOGLInitialized;
}
