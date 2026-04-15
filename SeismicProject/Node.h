#pragma once

#include"Model.h"

#include<string>

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
	Node(const char* name);
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

	std::string GetID();
	void SetID(const char* id);
protected:
	//For derived classes
	Node(const char* name, NodeType type);

	enum NodeType Type;
	std::string ID;
	
	std::vector<std::shared_ptr<Node>> ChildrenList;
};

