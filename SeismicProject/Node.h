#pragma once

#include"Model.h"

class Object;

class Node
{
public:
	enum NodeType
	{
		NODE,
		OBJECT,
		POINTLIGHT
	};
public:
	Node();
	~Node();

	virtual void Render(
		std::shared_ptr<Camera> camera,
		glm::vec3 pos = glm::vec3(0.0f), 
		glm::vec3 rot = glm::vec3(0.0f), 
		glm::vec3 sca = glm::vec3(1.0f)
	);

	virtual void Update();

	void AddChild();
	void AddChild(std::shared_ptr<Node> node);

	std::vector<std::shared_ptr<Node>>& GetChildrenList();

protected:
	enum NodeType Type;
	
	std::vector<std::shared_ptr<Node>> ChildrenList;
};

