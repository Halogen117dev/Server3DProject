#pragma once
#include<glad/glad.h>

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<vector>

class Mesh
{
public:
	//Mesh consists of vertices, parameters being said vertices
	//and number of vertices.
	Mesh(GLfloat* vertices, GLuint nVertices);
	Mesh(GLfloat* vertices, GLuint nVertices, GLuint* indices, GLuint nIndices);
	~Mesh();

	void CreateVertexData();

private:
	unsigned int
		VAO,
		VBO,
		EBO;
	std::vector<GLfloat> Vertices;
	std::vector<GLuint> Indices;
	bool IsIndexed;
public:
	//Getter methods for VAO/VBO
	GLuint GetVAO();
	GLuint GetVBO();
	GLuint GetEBO();
	bool GetIsIndexed();
	
	GLuint GetNumVertices();
	GLuint GetNumIndices();
};

