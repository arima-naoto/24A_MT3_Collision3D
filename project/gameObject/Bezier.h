#pragma once
#include "project/math/Pipeline/Rendering.h"

class Bezier : public Rendering{

public:

	Bezier() = default;

	~Bezier() = default;

	Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	void Draw(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

};

