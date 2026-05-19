#include "GameManager.h"

#include "WorkstationMonitorObject.h"
#include "WorkstationMaterial.h"

WorkstationMonitorObject::WorkstationMonitorObject(GameManager* game, const char* name)
	: Object(game, name, "resources/models/Monitor.obj")
{
	ServerStatus = 0;
	Time = 0;
	DT = 0;

	WorkMat = std::make_shared<WorkstationMaterial>();
	WorkMat->SetTexture("resources/images/Image_0.png");
	MyModel->SetMaterial(WorkMat);
}

WorkstationMonitorObject::~WorkstationMonitorObject()
{
}

void WorkstationMonitorObject::UpdateStatus(GLuint serverStatus, GLuint timeMS)
{
	ServerStatus = serverStatus;
	Time = timeMS;
}

void WorkstationMonitorObject::CustomUpdate()
{
	WorkMat->UpdateStatus(ServerStatus, Time);
}
