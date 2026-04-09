#include "Model.h"

Model::Model()
{
    float vertices[]
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
	mesh = std::make_unique<Mesh>(vertices, 9);

    shaderProgram = std::make_unique<ShaderProgram>();
    shaderProgram->AddShader(std::make_shared<VertexShader>());
    shaderProgram->AddShader(std::make_shared<FragmentShader>());
    shaderProgram->AttachAndLink();
}

Model::~Model()
{
    
}

void Model::Render()
{
    glUseProgram(shaderProgram->GetHandle());
    glBindVertexArray(mesh->GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
