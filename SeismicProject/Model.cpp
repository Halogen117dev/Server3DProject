#include "Model.h"

Model::Model()
{	
    ModelMatrix = glm::mat4(1.0f);
    Position = glm::vec3(0.0f);
    Rotation = glm::vec3(0.0f);
    Scale = glm::vec3(1.0f);


    //Vertex quadVertices[]
    //{
    //    //Vertex Positions                  //Normals Positions                 //Texture Coords
    //    glm::vec3(-0.5f, -0.5f, 0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(0.0f, 0.0f),
    //    glm::vec3(0.5f, -0.5f, 0.0f),       glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(1.0f, 0.0f),
    //    glm::vec3(0.5f, 0.5f, 0.0f),        glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(1.0f, 1.0f),
    //    glm::vec3(-0.5f, 0.5f, 0.0f),       glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(0.0f, 1.0f)
    //};
    //GLuint quadIndices[]
    //{
    //    0, 1, 2,
    //    0, 2, 3
    //};
    
    OBJLoader* objLoader = new OBJLoader();
    objLoader->LoadModel("resources/models/HP_Z8.obj");
    std::vector<Vertex> vertices = objLoader->GetVertices();
    Meshes.push_back(std::make_unique<Mesh>(vertices.data(), GLuint(vertices.size())));


    // WARNING
    // I HAVE SWITCHED THE COLOR CHANNELS INSIDE TEXTURE CLASS CONSTRUCTOR TO ALLOW FOR THIS SHII
    // CHANGE IT BACK

    Textures.push_back(std::make_unique<Texture>("resources/images/HP_Z8_low_Export_Material_BaseColor_1k.png"));

    MyShaderProgram = std::make_shared<ShaderProgram>();
    MyShaderProgram->AddShader(std::make_shared<VertexShader>("Vertex.vert"));
    MyShaderProgram->AddShader(std::make_shared<FragmentShader>("Fragment.frag"));
    MyShaderProgram->AttachAndLink();

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

    // WARNING
    // I HAVE SWITCHED THE COLOR CHANNELS INSIDE TEXTURE CLASS CONSTRUCTOR TO ALLOW FOR THIS SHII
    // CHANGE IT BACK

    Textures.push_back(std::make_unique<Texture>("resources/images/HP_Z8_low_Export_Material_BaseColor_1k.png"));

    MyShaderProgram = std::make_shared<ShaderProgram>();
    MyShaderProgram->AddShader(std::make_shared<VertexShader>("Vertex.vert"));
    MyShaderProgram->AddShader(std::make_shared<FragmentShader>("Fragment.frag"));
    MyShaderProgram->AttachAndLink();

    delete objLoader;
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

void Model::Render(
    std::shared_ptr<Camera> camera,
    glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 sca
)
{
    for (int i = 0; i < Meshes.size(); i++)
    {
        glUseProgram(MyShaderProgram->GetHandle());
        
        //TEXTURE UNIFORMS
        for (GLuint i = 0; i < Textures.size(); i++)
        {
            std::string textureName = "texture" + std::to_string(i);
            SetTextureUniform(i, textureName.c_str(), Textures[i]->GetHandle());
            //setTextureUniform(shaderProgram->GetHandle(), i, textureName.c_str(), Textures[i]->GetHandle());
        }

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

        SetVec3Uniform("lightPos", lightPos);
        SetVec3Uniform("cameraPos", cameraPos);

        //TEMP
        SetUintUniform("serverStatus", serverStatus);
        SetUintUniform("time", time);
        
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

void Model::SetShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
    MyShaderProgram = shaderProgram;
}

void Model::SetTexture(const char* texturePath)
{
    Textures.clear();
    Textures.push_back(std::make_unique<Texture>(texturePath));

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
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
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
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        1, 
        transpose, 
        glm::value_ptr(matrix)
    );
}

void Model::SetVec3Uniform(const char* uniformName, glm::vec3 vector)
{
    glUniform3fv(
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        1,
        glm::value_ptr(vector)
    );
}

void Model::SetUintUniform(const char* uniformName, GLuint uint)
{
    glUniform1ui(
        glGetUniformLocation(MyShaderProgram->GetHandle(), uniformName),
        uint
    );
}
