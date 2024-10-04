#include "Grid.h"

void Grid::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const float kGirdHalfWidth = 2.0f;
	const int32_t kSubdivision = 10;
	const float kGirdEvery = (kGirdHalfWidth * 2.0f) / float(kSubdivision);

	for (int32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		float x = -kGirdHalfWidth + (xIndex * kGirdEvery);

		Vector3 start = { x,0,-kGirdHalfWidth };
		Vector3 end = { x,0,kGirdHalfWidth };

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, x == 0.0f ? BLACK : color);

	}

	for (int32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		float z = -kGirdHalfWidth + (xIndex * kGirdEvery);

		Vector3 start = { -kGirdHalfWidth,0,z };
		Vector3 end = { kGirdHalfWidth,0,z };

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, z == 0.0f ? BLACK : color);

	}

}