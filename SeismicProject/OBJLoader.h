#pragma once

#include<glad/glad.h>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<memory>
#include<algorithm>

//#include<assimp/config.h>

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

private:
	Assimp::Importer MyImporter;
	std::unique_ptr<aiScene> MyScene;
	std::unique_ptr<aiNode> RootNode;

	std::vector<GLfloat> LoadModel(const char* modelPath);
};

