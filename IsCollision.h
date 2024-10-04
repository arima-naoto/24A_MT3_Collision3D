#pragma once
#include "project/math/Structure.h"

///AABBと球体の衝突判定
bool IsCollision(const AlignedBox& aabb, const  Spherical& sphere);

///AABBと線分の衝突判定
bool IsCollision(const AlignedBox& aabb, const Segment& segment);