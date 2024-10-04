#include "World.h"

void World::Initailize(Affine affine) {
	affine_ = affine;
}

Matrix4x4 World::CreateWorldMatrix(Affine affine) {
	
	Matrix4x4 worldMatrix = Rendering::SRTAffineMatrix(affine);

	return worldMatrix;
}