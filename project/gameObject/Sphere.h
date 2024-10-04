#pragma once
#include "project/math/Pipeline/Rendering.h"

class Sphere : public Rendering{

public:

	Sphere() = default;

	~Sphere() = default;

	void Draw(const Spherical& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

};

