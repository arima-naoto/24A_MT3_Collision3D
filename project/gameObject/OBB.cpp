#include "OBB.h"

void OBB::Initialize() {

	rotateMatrix = {};

	for (int32_t i = 0; i < 8; i++) {
		vertices_[i] = {};
	}

	worldMatrix_ = {};
}

void OBB::Draw(const Vector3& rotate, OrientedBox& obb,const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	this->Create_RotateMatrix(rotate, obb);

	this->Create_Vertices(vertices_, obb, viewProjectionMatrix, viewportMatrix);

	Novice::DrawLine((int)vertices_[0].x, (int)vertices_[0].y, (int)vertices_[1].x, (int)vertices_[1].y, color);
	Novice::DrawLine((int)vertices_[1].x, (int)vertices_[1].y, (int)vertices_[3].x, (int)vertices_[3].y, color);
	Novice::DrawLine((int)vertices_[3].x, (int)vertices_[3].y, (int)vertices_[2].x, (int)vertices_[2].y, color);
	Novice::DrawLine((int)vertices_[2].x, (int)vertices_[2].y, (int)vertices_[0].x, (int)vertices_[0].y, color);
	Novice::DrawLine((int)vertices_[4].x, (int)vertices_[4].y, (int)vertices_[5].x, (int)vertices_[5].y, color);
	Novice::DrawLine((int)vertices_[5].x, (int)vertices_[5].y, (int)vertices_[7].x, (int)vertices_[7].y, color);
	Novice::DrawLine((int)vertices_[7].x, (int)vertices_[7].y, (int)vertices_[6].x, (int)vertices_[6].y, color);
	Novice::DrawLine((int)vertices_[6].x, (int)vertices_[6].y, (int)vertices_[4].x, (int)vertices_[4].y, color);
	Novice::DrawLine((int)vertices_[0].x, (int)vertices_[0].y, (int)vertices_[4].x, (int)vertices_[4].y, color);
	Novice::DrawLine((int)vertices_[1].x, (int)vertices_[1].y, (int)vertices_[5].x, (int)vertices_[5].y, color);
	Novice::DrawLine((int)vertices_[2].x, (int)vertices_[2].y, (int)vertices_[6].x, (int)vertices_[6].y, color);
	Novice::DrawLine((int)vertices_[3].x, (int)vertices_[3].y, (int)vertices_[7].x, (int)vertices_[7].y, color);

}

void OBB::Create_RotateMatrix(const Vector3 &rotate,OrientedBox &obb){

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

	rotateMatrix = rotateXMatrix * (rotateYMatrix * rotateZMatrix);

	obb.orientations[0].x = rotateMatrix.m[0][0];
	obb.orientations[0].y = rotateMatrix.m[0][1];
	obb.orientations[0].z = rotateMatrix.m[0][2];

	obb.orientations[1].x = rotateMatrix.m[1][0];
	obb.orientations[1].y = rotateMatrix.m[1][1];
	obb.orientations[1].z = rotateMatrix.m[1][2];

	obb.orientations[2].x = rotateMatrix.m[2][0];
	obb.orientations[2].y = rotateMatrix.m[2][1];
	obb.orientations[2].z = rotateMatrix.m[2][2];


}

void OBB::Create_Vertices(Vector3 vertices[8], OrientedBox& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix){

	vertices[0] = { -obb.size.x, -obb.size.y, -obb.size.z };
	vertices[1] = {  obb.size.x, -obb.size.y, -obb.size.z };
	vertices[2] = { -obb.size.x,  obb.size.y, -obb.size.z };
	vertices[3] = {  obb.size.x,  obb.size.y, -obb.size.z };
	vertices[4] = { -obb.size.x, -obb.size.y,  obb.size.z };
	vertices[5] = {  obb.size.x, -obb.size.y,  obb.size.z };
	vertices[6] = { -obb.size.x,  obb.size.y,  obb.size.z };
	vertices[7] = {  obb.size.x,  obb.size.y,  obb.size.z };

	for (int i = 0; i < 8; ++i) {

		Matrix4x4 translateMatrix = Rendering::MakeTranslateMatrix(obb.center);

		worldMatrix_ = rotateMatrix * translateMatrix;

		vertices[i] = Transform(vertices[i], worldMatrix_);
		vertices[i] = Transform(vertices[i], viewProjectionMatrix);
		vertices[i] = Transform(vertices[i], viewportMatrix);
	}

}
