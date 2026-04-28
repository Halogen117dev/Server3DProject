#include"GameManager.h"

//Node::Node()
//{
//	ID = "Untitled Node";
//	Type = Node::NodeType::NODE;
//}

Node::Node(GameManager* game, const char* name)
{
	ID = name;
	Type = Node::NodeType::NODE;
	Game = game;
}

Node::~Node()
{
	// DO NOT DELETE GAME
	// IT'S NOT WORTH IT
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
	CustomUpdate();

	//do update stuff
	for (int i = 0; i < ChildrenList.size(); i++)
	{
		ChildrenList[i]->Update();
	}
}

void Node::CustomUpdate()
{
	
}

std::shared_ptr<Node> Node::AddChild()
{
	std::shared_ptr<Node> node;
	ChildrenList.push_back(node);
	Game->AddNodeToMap(node);

	return node;
}

std::shared_ptr<Node> Node::AddChild(std::shared_ptr<Node> node)
{
	ChildrenList.push_back(node);
	return node;
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


