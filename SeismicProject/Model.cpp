#include "Model.h"
#include"OBJLoader.h"

Model::Model()
{	
    ModelMatrix = glm::mat4(1.0f);
    Position = glm::vec3(0.0f);
    Rotation = glm::vec3(0.0f);
    Scale = glm::vec3(1.0f);
    
    OBJLoader* objLoader = new OBJLoader();
    objLoader->LoadModel("resources/models/HP_Z8.obj");
    std::vector<Vertex> vertices = objLoader->GetVertices();
    Meshes.push_back(std::make_unique<Mesh>(vertices.data(), GLuint(vertices.size())));

    MyMaterial = std::make_shared<Material>();

    delete objLoader;
}

Model::Model(const char* modelPath)
{
    ModelMatrix = glm::mat4(1.0f);
    Position = glm::vec3(0.0f);
    Rotation = glm::vec3(0.0f);
    Scale = glm::vec3(1.0f);

    OBJLoader* objLoader = new OBJLoader();
    objLoader->LoadModel(modelPath);
    std::vector<Vertex> vertices = objLoader->GetVertices();
    Meshes.push_back(std::make_unique<Mesh>(vertices.data(), vertices.size()));

    MyMaterial = std::make_shared<Material>();


    delete objLoader;
}

Model::~Model()
{
    
}

void Model::Render(
    std::shared_ptr<Camera> camera,
    glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 sca
)
{
    for (int i = 0; i < Meshes.size(); i++)
    {
        MyMaterial->ReadyShader();

        //MODEL MATRIX CALCULATIONS
        ModelMatrix = glm::mat4(1.0f);
        TransformMatrix(Position, Rotation, Scale);

        //External transformations
        TransformMatrix(pos, rot,sca);        

        //TESTING LIGHT STUFF
        glm::vec3 lightPos(-3.0f, 2.0f, 2.0f);
        glm::vec3 cameraPos = camera->GetPosition();


        //MODEL MATRIX UNIFORM
        SetMat4Uniform("ModelMatrix", ModelMatrix, GL_FALSE);
        SetMat4Uniform("ViewMatrix", camera->GetViewMatrix(), GL_FALSE);
        SetMat4Uniform("ProjectionMatrix", camera->GetProjectionMatrix(), GL_FALSE);


        // Removed for default model
        SetVec3Uniform("lightPos", lightPos);
        SetVec3Uniform("cameraPos", cameraPos);
        
        glBindVertexArray(Meshes[i]->GetVAO());
        if (Meshes[i]->GetIsIndexed())
        {
            glDrawElements(GL_TRIANGLES, Meshes[i]->GetNumIndices(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            //glDrawArrays(GL_TRIANGLES, 0, Meshes[i]->GetNumVertices()/GLuint(3));
            glDrawArrays(GL_TRIANGLES, 0, Meshes[i]->GetNumVertices());
        }

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0); 
    }      
}

void Model::SetMaterial(std::shared_ptr<Material> material)
{
    MyMaterial = material;
}

void Model::TransformMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
    ModelMatrix = glm::translate(ModelMatrix, pos);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    ModelMatrix = glm::scale(ModelMatrix, sca);
}

void Model::TransformMatrix(glm::mat4 transformMatrix)
{
    
}



void Model::SetTextureUniform
(
    GLuint textureNumber, 
    const char* uniformName, 
    GLuint textureHandle
)
{
    glUniform1i(
        glGetUniformLocation(MyMaterial->GetShaderProgramHandle(), uniformName),
        textureNumber
    );

    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void Model::SetMat4Uniform
(
    const char* uniformName, 
    glm::mat4 matrix,
    GLboolean transpose
)
{
    glUniformMatrix4fv(
        glGetUniformLocation(MyMaterial->GetShaderProgramHandle(), uniformName),
        1, 
        transpose, 
        glm::value_ptr(matrix)
    );
}

void Model::SetVec3Uniform(const char* uniformName, glm::vec3 vector)
{
    glUniform3fv(
        glGetUniformLocation(MyMaterial->GetShaderProgramHandle(), uniformName),
        1,
        glm::value_ptr(vector)
    );
}

void Model::SetUintUniform(const char* uniformName, GLuint uint)
{
    glUniform1ui(
        glGetUniformLocation(MyMaterial->GetShaderProgramHandle(), uniformName),
        uint
    );
}
