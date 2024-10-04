#pragma once
#include "project/math/Pipeline/Rendering.h"

class Grid : public Rendering{

public:

	Grid() = default;

	~Grid() = default;

	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
};

