#pragma once
#include "Novice.h"

struct Vector2 {
	int x;
	int y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {

	float m[4][4];

};

struct Affine{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

template<typename Ty_>
struct Fov {

	Ty_ fovY;
	Ty_ aspectRatio;
	Ty_ nearClip;
	Ty_ farClip;
};

template<typename Ty_>
struct ViewRect {

	Ty_ left;
	Ty_ top;
	Ty_ width;
	Ty_ height;
	Ty_ minDepth;
	Ty_ maxDepth;

};

struct Spherical {

	Vector3 center;
	float radius;

};

struct Segment {
	Vector3 origin;//始点
	Vector3 diff; //終点への差分ベクトル
};

struct Plane {

	Vector3 normal;//法線
	float distance;//距離
};

struct Triangle {
	Vector3 vertices[3];
};

struct AlignedBox {

	Vector3 min;//最小店
	Vector3 max;//最大店

};

struct OrientedBox {

	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;

};

