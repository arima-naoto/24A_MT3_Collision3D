#pragma once
#include "project/math/Pipeline/Rendering.h"

class World: public Rendering{

public:

	World() = default;

	~World() = default;

	void Initailize(Affine affine);

	Matrix4x4 CreateWorldMatrix(Affine affine);

private:

	Affine affine_;

};

