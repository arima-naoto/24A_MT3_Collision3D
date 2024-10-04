#define NOMINMAX
#include "IsCollision.h"
#include "project/math/Arithmetic.h"
#define _USE_MATH_DEFINES
#include "cmath"
#include "algorithm"

bool IsCollision(const AlignedBox& aabb, const  Spherical& sphere) {

	// 最近接点を求める
	Vector3 closestPoint;
	closestPoint.x = std::clamp(sphere.center.x, aabb.min.x, aabb.max.x);
	closestPoint.y = std::clamp(sphere.center.y, aabb.min.y, aabb.max.y);
	closestPoint.z = std::clamp(sphere.center.z, aabb.min.z, aabb.max.z);

	// 最近接点と球の中心との距離を求める
	float distance = Calculator::Length(closestPoint - sphere.center);

	// 距離が半径よりも小さいかどうかを判定
	return distance <= sphere.radius;

}

bool IsCollision(const AlignedBox& aabb, const Segment& segment) {

	// 各方向の t 値の計算
	float tNearX = (aabb.min.x - segment.origin.x) / segment.diff.x;
	float tFarX = (aabb.max.x - segment.origin.x) / segment.diff.x;
	if (tNearX > tFarX) std::swap(tNearX, tFarX);

	float tNearY = (aabb.min.y - segment.origin.y) / segment.diff.y;
	float tFarY = (aabb.max.y - segment.origin.y) / segment.diff.y;
	if (tNearY > tFarY) std::swap(tNearY, tFarY);

	float tNearZ = (aabb.min.z - segment.origin.z) / segment.diff.z;
	float tFarZ = (aabb.max.z - segment.origin.z) / segment.diff.z;
	if (tNearZ > tFarZ) std::swap(tNearZ, tFarZ);

	// AABBとの衝突点(貫通点)の t が小さい方
	float tmin = std::max(std::max(tNearX, tNearY), tNearZ);
	// AABBとの衝突点(貫通点)の t が大きい方
	float tmax = std::min(std::min(tFarX, tFarY), tFarZ);

	// tmin が tmax 以下で、かつ tmax が0から1の間にあるかどうかをチェック
	return (tmin <= tmax) && (tmax >= 0) && (tmin <= 1);

}