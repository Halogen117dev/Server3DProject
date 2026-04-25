#pragma once


#include<glad/glad.h>

#include"Vertex.h"

#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<memory>
#include<algorithm>

//#include<assimp/config.h>

//struct Vertex
//{
//	glm::vec3 Position;
//	glm::vec3 Normal;
//	glm::vec2 UVCoord;
//};

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	std::vector<Vertex> GetVertices();
	std::vector<GLuint> GetIndices();

	void LoadModel(const char* modelPath);

private:
	std::vector<Vertex> OutVertices;
	std::vector<GLuint> OutIndices;
};

