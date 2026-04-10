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
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 UVCoord;
	};

	//Mesh consists of vertices, parameters being said vertices
	//and number of vertices.
	Mesh(Vertex* vertices, GLuint nVertices);
	Mesh(Vertex* vertices, GLuint nVertices, GLuint* indices, GLuint nIndices);
	~Mesh();

private:
	void CreateVertexData();

	unsigned int
		VAO,
		VBO,
		EBO;
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	bool IsIndexed;
public:
	//Getter methods
	GLuint GetVAO();
	GLuint GetVBO();
	GLuint GetEBO();
	bool GetIsIndexed();
	
	GLuint GetNumVertices();
	GLuint GetNumIndices();
};

