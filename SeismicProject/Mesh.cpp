#include "Mesh.h"

Mesh::Mesh(GLfloat* vertices, GLuint nVertices)
{
	for (GLuint i = 0; i < nVertices; i++)
	{
		Vertices.push_back(vertices[i]);
	}

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(GLfloat), Vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
}

GLuint Mesh::GetVAO()
{
    return VAO;
}

GLuint Mesh::GetVBO()
{
    return VBO;
}
