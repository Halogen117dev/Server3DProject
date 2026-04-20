#pragma once
#include<wx/wx.h>

#include"Node.h"
#include"Object.h"

#include<vector>
#include<memory>

class GameManager
{
public:
	GameManager();
	~GameManager();

	//
	void Update();

	//Returns the vector filled with every single model in the program
	//Right now, it just returns whatever the actual ModelList vector is
	//Later, it will have an Object3D list instead of a ModelList, and the
	//function will iterate through every Object3D to give the ModelList or
	//some shit bro I don't know to be honest.
	//
	//Making it return a reference to the list instead of a copy.
	std::shared_ptr<Node> GetMainNode();
	std::shared_ptr<Camera>& GetCamera();


private:
	std::shared_ptr<Node> MainNode;
	std::shared_ptr<Camera> MainCamera;

	glm::vec3 rotation1 = glm::vec3(0.0f);
	glm::vec3 rotation2 = glm::vec3(0.0f);
};

