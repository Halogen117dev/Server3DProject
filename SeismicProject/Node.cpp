#include "Node.h"

Node::Node()
{
	ID = "Untitled Node";
	Type = Node::NodeType::NODE;
}

Node::Node(const char* name)
{
	ID = name;
	Type = Node::NodeType::NODE;
}

Node::Node(const char* name, NodeType type)
{
	ID = name;
	Type = type;
}

Node::~Node()
{

}

void Node::Render(std::shared_ptr<Camera> camera, glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	for (int i = 0; i < ChildrenList.size(); i++)
	{
		ChildrenList[i]->Render(camera, pos, rot, sca);
	}
}

void Node::Update()
{
	//do update stuff
	for (int i = 0; i < ChildrenList.size(); i++)
	{
		ChildrenList[i]->Update();
	}
}

void Node::AddChild()
{
	ChildrenList.push_back(std::make_shared<Node>());
}

void Node::AddChild(std::shared_ptr<Node> node)
{
	ChildrenList.push_back(node);
}

std::vector<std::shared_ptr<Node>>& Node::GetChildrenList()
{
	return ChildrenList;
}

std::string Node::GetID()
{
	return ID;
}

void Node::SetID(const char* id)
{
	ID = id;
}


