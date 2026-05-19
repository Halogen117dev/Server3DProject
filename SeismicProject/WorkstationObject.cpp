#include "GameManager.h"

#include "WorkstationObject.h"
#include "WorkstationMaterial.h"
#include "WorkstationMonitorObject.h"


WorkstationObject::WorkstationObject(GameManager* game, const char* name)
	: Object(game, name, "resources/models/HP_Z8.obj")
{
	WorkMat = std::make_shared<WorkstationMaterial>();
	MyModel->SetMaterial(WorkMat);

	ChildMonitor = std::make_shared<WorkstationMonitorObject>(game, std::string(name).append("-monitor").c_str());
	AddChild(ChildMonitor);
	ChildMonitor->Translate(glm::vec3(-0.35f, 0.0f, -0.1f));
	ChildMonitor->Rotate(glm::vec3(0.0f, -55.0f, 0.0f));
}

WorkstationObject::~WorkstationObject()
{
}

void WorkstationObject::CustomUpdate()
{
	GLuint serverStatus;
	if (!Game->GetWorkstationState(ID.c_str()).PowerState)
	{
		serverStatus = 0;
	}
	else
	{
		if (Game->GetWorkstationState(ID.c_str()).Status)
			serverStatus = 1;
		else
			serverStatus = 2;
	}
	ChildMonitor->UpdateStatus(serverStatus, Game->Time());
	WorkMat->UpdateStatus(serverStatus, Game->Time());
}