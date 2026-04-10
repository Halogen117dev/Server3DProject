#include "Model.h"

Model::Model()
{	
    Mesh::Vertex quadVertices[]
    {
        //Vertex Positions                          //Texture Coords
        glm::vec3(- 0.5f, -0.5f, 0.5f),             glm::vec2(0.0f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.5f),               glm::vec2(1.0f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),                glm::vec2(1.0f, 1.0f),
        glm::vec3(-0.5f, 0.5f, 0.5f),               glm::vec2(0.0f, 1.0f)
    };
    GLuint quadIndices[]
    {
        0, 1, 2,
        0, 2, 3
    };

    //Meshes.push_back(std::make_unique<Mesh>(vertices, 9));
    Meshes.push_back(std::make_unique<Mesh>(quadVertices, 4, quadIndices, 6));
    //mesh = std::make_unique<Mesh>(vertices, 9);
    //mesh = std::make_unique<Mesh>(quadVertices, 12, quadIndices, 6);

    Textures.push_back(std::make_unique<Texture>("resources/images/master_chief.png"));
    Textures.push_back(std::make_unique<Texture>("resources/images/bird.png"));

    shaderProgram = std::make_unique<ShaderProgram>();
    shaderProgram->AddShader(std::make_shared<VertexShader>());
    shaderProgram->AddShader(std::make_shared<FragmentShader>());
    shaderProgram->AttachAndLink();
}

Model::~Model()
{
    
}


//HELPER FUNCTION FOR TEXTURE UNIFORMS
void setTextureUniform(GLuint shaderProgramHandle, GLuint textureNumber, const char* uniformName, GLuint textureHandle)
{
    glUniform1i(glGetUniformLocation(shaderProgramHandle, uniformName), textureNumber);

    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void Model::Render()
{
    for (int i = 0; i < Meshes.size(); i++)
    {
        glUseProgram(shaderProgram->GetHandle());
        
        for (GLuint i = 0; i < Textures.size(); i++)
        {
            std::string textureName = "texture" + std::to_string(i);
            setTextureUniform(shaderProgram->GetHandle(), i, textureName.c_str(), Textures[i]->GetHandle());
        }
        
        glBindVertexArray(Meshes[i]->GetVAO());
        if (Meshes[i]->GetIsIndexed())
        {
            glDrawElements(GL_TRIANGLES, Meshes[i]->GetNumIndices(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            //glDrawArrays(GL_TRIANGLES, 0, Meshes[i]->GetNumVertices()/GLuint(3));
        }

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0); 
    }      
}
