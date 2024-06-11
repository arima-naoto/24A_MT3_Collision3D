#pragma once
#include "Vector3.h"

/// <summary>
/// アフィン構造体
/// </summary>
struct Affine
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

/// <summary>
/// 球体の構造体
/// </summary>
struct Sphere
{
	Vector3 center;
	float radius;
};

/// <summary>
/// 線分構造体
/// </summary>
struct Segment 
{
	Vector3 origin;
	Vector3 diff;
};