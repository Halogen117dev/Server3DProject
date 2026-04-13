#pragma once

#include"Model.h"

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
	std::vector<std::shared_ptr<Model>>& GetModelList();
	std::shared_ptr<Camera>& GetCamera();


private:
	std::vector<std::shared_ptr<Model>> ModelList;
	std::shared_ptr<Camera> MainCamera;
};

