#include "Node.h"

Node::Node()
{
	Type = Node::NodeType::NODE;
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