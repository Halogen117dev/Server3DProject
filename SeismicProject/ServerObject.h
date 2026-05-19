#pragma once
#include "Object.h"

#include "WorkstationMaterial.h"


class ServerObject : public Object
{
public:
	ServerObject(GameManager* game, const char* name);
	~ServerObject();

	void CustomUpdate() override;
private:
	std::shared_ptr<WorkstationMaterial> WorkMat;
};

