#include "Model.h"

Model::Model()
{	
    ModelMatrix = glm::mat4(1.0f);

    //Transformation tutorial
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f));

    Mesh::Vertex quadVertices[]
    {
        //Vertex Positions                          //Texture Coords
        glm::vec3(- 0.5f, -0.5f, 0.0f),             glm::vec2(0.0f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),               glm::vec2(1.0f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),                glm::vec2(1.0f, 1.0f),
        glm::vec3(-0.5f, 0.5f, 0.0f),               glm::vec2(0.0f, 1.0f)
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

void Model::Render(std::shared_ptr<Camera> camera)
{
    for (int i = 0; i < Meshes.size(); i++)
    {
        glUseProgram(shaderProgram->GetHandle());
        
        //TEXTURE UNIFORMS
        for (GLuint i = 0; i < Textures.size(); i++)
        {
            std::string textureName = "texture" + std::to_string(i);
            setTextureUniform(shaderProgram->GetHandle(), i, textureName.c_str(), Textures[i]->GetHandle());
        }


        //TESTING
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f));
        //TESTING

        //MODEL MATRIX UNIFORM
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram->GetHandle(), "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram->GetHandle(), "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram->GetHandle(), "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));



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
