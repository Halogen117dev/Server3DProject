#include "Model.h"

Model::Model()
{
    GLfloat vertices[]
    {
        -0.7f, -0.7f, 0.0f,
        0.7f, -0.7f, 0.0f,
        0.0f, 0.7f, 0.0f
    };
    GLuint indices[]
    {
        0,
        1,
        2
    };
	
    GLfloat quadVertices[]
    {
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
    };
    GLuint quadIndices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    Meshes.push_back(std::make_unique<Mesh>(vertices, 9));
    Meshes.push_back(std::make_unique<Mesh>(quadVertices, 12, quadIndices, 6));
    //mesh = std::make_unique<Mesh>(vertices, 9);
    //mesh = std::make_unique<Mesh>(quadVertices, 12, quadIndices, 6);

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
    for (int i = 0; i < Meshes.size(); i++)
    {
        glUseProgram(shaderProgram->GetHandle());
        glBindVertexArray(Meshes[i]->GetVAO());
        if (Meshes[i]->GetIsIndexed())
        {
            glDrawElements(GL_TRIANGLES, Meshes[i]->GetNumIndices(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, Meshes[i]->GetNumVertices()/GLuint(3));
        }
    }      
}
