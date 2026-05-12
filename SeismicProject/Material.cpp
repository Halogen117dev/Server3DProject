#include "Material.h"

Material::Material()
{
    MyShaderProgram = std::make_unique<ShaderProgram>();
    MyShaderProgram->AddShader(std::make_shared<VertexShader>("Default.vert"));
	MyShaderProgram->AddShader(std::make_shared<FragmentShader>("Default.frag"));
    MyShaderProgram->AttachAndLink();

    Textures.push_back(std::make_unique<Texture>("resources/images/error.png", GL_RGB, GL_RGB));
}

Material::~Material()
{

}

void Material::ReadyShader()
{
    glUseProgram(MyShaderProgram->GetHandle());

	//TEXTURE UNIFORMS
    for (GLuint i = 0; i < Textures.size(); i++)
    {
        std::string textureName = "texture" + std::to_string(i);
        SetTextureUniform(i, textureName.c_str(), Textures[i]->GetHandle());
        //setTextureUniform(shaderProgram->GetHandle(), i, textureName.c_str(), Textures[i]->GetHandle());
    }
}





//UNIFORM SETTERS

GLuint Material::GetShaderProgramHandle()
{
    return MyShaderProgram->GetHandle();
}

void Material::SetTextureUniform
(
    GLuint textureNumber, 
    const char* uniformName, 
    GLuint textureHandle
)
{
    glUniform1i(
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        textureNumber
    );

    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void Material::SetMat4Uniform
(
    const char* uniformName, 
    glm::mat4 matrix,
    GLboolean transpose
)
{
    glUniformMatrix4fv(
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        1, 
        transpose, 
        glm::value_ptr(matrix)
    );
}

void Material::SetVec3Uniform(const char* uniformName, glm::vec3 vector)
{
    glUniform3fv(
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        1,
        glm::value_ptr(vector)
    );
}

void Material::SetUintUniform(const char* uniformName, GLuint uint)
{
    glUniform1ui(
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        uint
    );
}
