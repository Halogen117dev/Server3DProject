#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, GLuint nVertices)
{
	for (GLuint i = 0; i < nVertices; i++)
	{
		Vertices.push_back(vertices[i]);
	}
    VAO = 0;
    VBO = 0;
    EBO = 0;
    IsIndexed = false;
    CreateVertexData();
}

Mesh::Mesh(Vertex* vertices, GLuint nVertices, GLuint* indices, GLuint nIndices)
{
    for (GLuint i = 0; i < nVertices; i++)
    {
        Vertices.push_back(vertices[i]);
    }
    
    for (GLuint i = 0; i < nIndices; i++)
    {
        Indices.push_back(indices[i]);
    }
    VAO = 0;
    VBO = 0;
    EBO = 0;
    IsIndexed = true;
    CreateVertexData();
}

Mesh::~Mesh()
{
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
}

void Mesh::CreateVertexData()
{
    if (Indices.size() == 0)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);
        
        //Link attributes (set pointers)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);   //layout = 0 in vertex shader

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);   //layout = 1 in vertex shader

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    else
    {
        glGenVertexArrays(1, &VAO);     // Vertex array
        glGenBuffers(1, &VBO);          // Vertex buffer
        glGenBuffers(1, &EBO);          // Element buffer

        glBindVertexArray(VAO);

        //VBO STUFF (vertices time)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

        //EBO STUFF (indices time)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), Indices.data(), GL_STATIC_DRAW);

        //Link attributes (set pointers)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);   //layout = 0 in vertex shader

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);   //layout = 1 in vertex shader

        //unbind all the stuff. Apparently, we won't be needing VBO/EBO from now on,
        //so might aswell get rid of them later.
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

GLuint Mesh::GetVAO()
{
    return VAO;
}

GLuint Mesh::GetVBO()
{
    return VBO;
}

GLuint Mesh::GetEBO()
{
    return EBO;
}

bool Mesh::GetIsIndexed()
{
    return IsIndexed;
}

GLuint Mesh::GetNumVertices()
{
    return Vertices.size();
}

GLuint Mesh::GetNumIndices()
{
    return Indices.size();
}
