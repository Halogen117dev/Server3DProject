#include "GameManager.h"

#include "ServerObject.h"
#include "WorkstationMaterial.h"

ServerObject::ServerObject(GameManager* game, const char* name)
	: Object(game, name, "resources/models/Dell_R710.obj")
{
	WorkMat = std::make_shared<WorkstationMaterial>();
	WorkMat->SetTexture("resources/images/DellR710_Color_1k.png", GL_RGB, GL_RGBA);
	MyModel->SetMaterial(WorkMat);
}

ServerObject::~ServerObject()
{
}

void ServerObject::CustomUpdate()
{
	GLuint serverStatus;
	if (Game->GetServerState(ID.c_str()).UnknownStatus)
	{
		serverStatus = 0;
	}
	else
	{
		if (!Game->GetServerState(ID.c_str()).PowerState)
		{
			serverStatus = 1;
		}
		else
		{
			serverStatus = 2;
		}
	}

	WorkMat->UpdateStatus(serverStatus, Game->Time());
}
