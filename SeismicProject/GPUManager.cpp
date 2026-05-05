#include "GPUManager.h"
#include "Model.h"

GPUManager::GPUManager(wxGLContext* openGLContext, wxGLCanvas* parentGLCanvas)
	: 
    OGLContext(openGLContext),
    ParentGLCanvas(parentGLCanvas)
{
    BGColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    FBO = 0;
    RBO = 0;
    FramebufferTexture = 0;
    RectVAO = RectVBO = 0;
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

    //ModelList.push_back(std::make_shared<Model>());

    IsOGLInitialized = true;


    //Framebuffer shaderprogram
    FrameBufferShaderProgram = std::make_unique<ShaderProgram>();

    FrameBufferShaderProgram->AddShader(std::make_unique<VertexShader>("Framebuffer.vert"));
    FrameBufferShaderProgram->AddShader(std::make_unique<FragmentShader>("Framebuffer.frag"));
    FrameBufferShaderProgram->AttachAndLink();
    glUseProgram(FrameBufferShaderProgram->GetHandle());
    glUniform1i(glGetUniformLocation(FrameBufferShaderProgram->GetHandle(), "screenTexture"), 0);
    
    //Framebuffer RECT creation
    GLfloat rectVerts[] =
    {
        // Pos         // UV
		-1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f

    };
    
    glGenVertexArrays(1, &RectVAO);
    glGenBuffers(1, &RectVBO);
    glBindVertexArray(RectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, RectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVerts), &rectVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));



    //OPENGL Options
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //GenerateFBORBO(ParentGLCanvas->GetClientSize().x, ParentGLCanvas->GetClientSize().y);
    GenerateFBORBO(1920, 1080);

    return true;
}

bool GPUManager::Render(std::shared_ptr<Camera> camera, std::shared_ptr<Node> mainNode)
{
    //First stage
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClearColor(BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    mainNode->Render(camera);

    //Second stage
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(FrameBufferShaderProgram->GetHandle());
	glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(RectVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, FramebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
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

void GPUManager::GenerateFBORBO(int width, int height)
{
	//window sizes
    width = ParentGLCanvas->GetClientSize().x;
    height = ParentGLCanvas->GetClientSize().y;

    /*if (FBO)
        glDeleteFramebuffers(1, &FBO);*/
    //FRAMEBUFFER
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    /*if (FramebufferTexture)
        glDeleteTextures(1, &FramebufferTexture);*/
    //FRAMEBUFFER TEXTURE
	glGenTextures(1, &FramebufferTexture);
	glBindTexture(GL_TEXTURE_2D, FramebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FramebufferTexture, 0);
    
    /*if (RBO)
        glDeleteRenderbuffers(1, &RBO);*/
    //RENDERBUFFER
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		throw;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
