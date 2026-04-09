#pragma once
#include<glad/glad.h>

#include<vector>

class Mesh
{
public:
	//Mesh consists of vertices, parameters being said vertices
	//and number of vertices.
	Mesh(float* vertices, int nVertices);
	~Mesh();

private:
	unsigned int
		VAO,
		VBO;
	std::vector<float> Vertices;

public:
	//Getter methods for VAO/VBO
	unsigned int GetVAO();
	unsigned int GetVBO();
};

