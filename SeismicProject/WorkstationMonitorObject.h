#pragma once
#include "Object.h"

#include "WorkstationMaterial.h"

class WorkstationMonitorObject : public Object
{
public:
    WorkstationMonitorObject(GameManager* game, const char* name);
	~WorkstationMonitorObject();
	
	// Takes two inputs and updates the uniforms accordingly; passes it onto materials.
	// Server status is inferred as 1->Powered Off, 2->Powered On with No Users (Offline),
	// 3->Powered On with Users (Online)
	// Time is in milliseconds.
	void UpdateStatus(GLuint serverStatus, GLuint timeMS);	
	
	void CustomUpdate() override;

private:
	GLuint
		ServerStatus,
		Time,
		DT;

	std::shared_ptr<WorkstationMaterial> WorkMat;
};

