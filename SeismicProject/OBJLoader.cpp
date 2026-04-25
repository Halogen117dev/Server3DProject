#include "OBJLoader.h"

#include<Windows.h>

OBJLoader::OBJLoader()
{
	
}

OBJLoader::~OBJLoader()
{
}

std::vector<Vertex> OBJLoader::GetVertices()
{
	std::vector<Vertex> out;
	for (int i = 0; i < OutVertices.size(); i++)
	{
		out.push_back(OutVertices[i]);
	}

	return out;
}

std::vector<GLuint> OBJLoader::GetIndices()
{
	std::vector<GLuint> out;
	for (int i = 0; i < OutIndices.size(); i++)
	{
		out.push_back(OutIndices[i]);
	}

	return out;
}

/*
void OBJLoader::LoadModel(const char* modelPath)
{
	std::vector<unsigned int> posIndices, uvCoordIndices, normIndices;
	std::vector<glm::vec3> tempPos;
	std::vector<glm::vec2> tempUvCoords;
	std::vector<glm::vec3> tempNormals;

	FILE* file = fopen(modelPath, "r");

	
	while (1)
	{		
		char lineHeader[256];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 pos;
			fscanf(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			tempPos.push_back(pos);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 norm;
			fscanf(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
			tempNormals.push_back(norm);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uvCoord;
			fscanf(file, "%f %f\n", &uvCoord.x, &uvCoord.y);
			tempUvCoords.push_back(uvCoord);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int posIndex[3], uvIndex[3], normIndex[3];
			fscanf(file, "%d/%d/%d %d/%d%d %d/%d/%d\n", &posIndex[0], &normIndex[0], &uvIndex[0], &posIndex[1], &normIndex[1], &uvIndex[1], &posIndex[2], &normIndex[2], &uvIndex[2]);
			//fscanf(file, "%d/%d/%d %d/%d%d %d/%d/%d\n", &posIndex[0], &uvIndex[0], &normIndex[0], &posIndex[1],&uvIndex[1], &normIndex[1], &posIndex[2], &uvIndex[2], &normIndex[2]);

			posIndices.push_back(posIndex[0]);
			posIndices.push_back(posIndex[1]);
			posIndices.push_back(posIndex[2]);
			uvCoordIndices.push_back(uvIndex[0]);
			uvCoordIndices.push_back(uvIndex[1]);
			uvCoordIndices.push_back(uvIndex[2]);
			normIndices.push_back(normIndex[0]);
			normIndices.push_back(normIndex[1]);
			normIndices.push_back(normIndex[2]);
		}
	}
	
	OutIndices.clear();
	OutVertices.clear();
	for (int i = 0; i < posIndices.size(); i++)
	{
		unsigned int posIndex = posIndices[i];
		unsigned int uvIndex = uvCoordIndices[i];
		unsigned int normIndex = normIndices[i];


		glm::vec3 pos = tempPos[posIndex - 1];
		glm::vec2 uv = tempUvCoords[uvIndex - 1];
		glm::vec3 norm = tempNormals[normIndex - 1];

		GLuint index = posIndex - 1;

		OutVertices.push_back(
			Vertex(pos, norm, uv)
		);

		OutIndices.push_back(index);
	}
}
*/

void OBJLoader::LoadModel(const char* modelPath)
{
	std::vector<glm::vec3> tempPos;
	std::vector<glm::vec2> tempUv;
	std::vector<glm::vec3> tempNorm;

	std::vector<GLuint>
		posIndices,
		uvIndices,
		normIndices;

	std::stringstream ss;
	std::ifstream file(modelPath);
	std::string line = "";
	std::string prefix = "";

	//Temporary holders for pos/uv/norm
	glm::vec3 tempVec3;
	glm::vec2 tempVec2;
	GLuint tempGLuint;

	if (!file.is_open())
	{
		std::stringstream sstream;
		sstream << "Sheisse\nMAJOR ERROR\nFILE WON'T OPEN\n";
		OutputDebugStringA(sstream.str().c_str());
	}

	//Getting each line
	while (std::getline(file, line))
	{
		//Getting line prefix
		ss.str(line);
		ss >> prefix;

		if (prefix == "v")
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			tempPos.push_back(tempVec3);
		}
		else if (prefix == "vt")
		{
			ss >> tempVec2.x >> tempVec2.y;
			tempUv.push_back(tempVec2);
		}
		else if (prefix == "vn")
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			tempNorm.push_back(tempVec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> tempGLuint)
			{
				if (counter == 0)
					posIndices.push_back(tempGLuint);
				else if (counter == 1)
					uvIndices.push_back(tempGLuint);
				else if (counter == 2)
					normIndices.push_back(tempGLuint);


				//Handling slashes
				if (ss.peek() == '/')
				{
					counter++;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					counter++;
					ss.ignore(1, ' ');
				}

				if (counter > 2)
				{
					counter = 0;
				}
			}
		}

		//Clear stringstream after each use
		ss.clear();
	}

	//Clearing temp arrays
	OutVertices.clear();
	OutIndices.clear();


	for (int i = 0; i < posIndices.size(); i++)
	{
		Vertex vertex;
		vertex.Position = tempPos[posIndices[i] - 1];
		vertex.Normal = tempNorm[normIndices[i] - 1];
		vertex.UVCoord= tempUv[uvIndices[i] - 1];
		OutVertices.push_back(vertex);
	}

}