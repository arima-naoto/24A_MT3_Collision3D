#pragma once
#include "Vector3.h"

/// アフィン構造体
struct Affine
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

/// 球体の構造体
struct Sphere
{
	Vector3 center;
	float radius;
};