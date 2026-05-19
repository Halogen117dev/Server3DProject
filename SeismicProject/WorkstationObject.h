#pragma once
#include "Object.h"

#include "WorkstationMaterial.h"

class WorkstationMonitorObject;

class WorkstationObject : public Object
{
public:
	WorkstationObject(GameManager* game, const char* name);

	~WorkstationObject();

	void CustomUpdate() override;
private:
	std::shared_ptr<WorkstationMaterial> WorkMat;
	
	std::shared_ptr<WorkstationMonitorObject> ChildMonitor;
};

