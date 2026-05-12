#pragma once
#include"Material.h"

class FloorMaterial : public Material
{
public:
	FloorMaterial();
	~FloorMaterial();

	void ReadyShader() override;
};

