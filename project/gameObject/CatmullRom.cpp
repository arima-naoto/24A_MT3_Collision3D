#include "CatmullRom.h"

Vector3 CatmullRom::Lerp(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t) {

	const float s = 0.5f;

	float t2 = t * t;
	float t3 = t2 * t;

	Vector3 e0 = 2 * p1;
	Vector3 e1 = -p0 + p2;
	Vector3 e2 = 2 * p0 - 5 * p1 + 4 * p2 - p3;
	Vector3 e3 = -p0 + 3 * p1 - 3 * p2 + p3;

	return s * (e3 * t3 + e2 * t2 + e1 * t + e0);
}

void CatmullRom::Draw(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Vector3& controlPoint3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const int resolution = 20;
	float step = 1.0f / resolution;

	// 初期の位置を設定
	Vector3 previousPoint = controlPoint1;

	for (int i = 1; i <= resolution; ++i) {
		float t = step * i;

		Vector3 currentPoint = CatmullRom::Lerp(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t);

		Vector3 previousScreenPoint = Rendering::Transform(previousPoint, viewProjectionMatrix);
		previousScreenPoint = Rendering::Transform(previousScreenPoint, viewportMatrix);

		Vector3 currentScreenPoint = Rendering::Transform(currentPoint, viewProjectionMatrix);
		currentScreenPoint = Rendering::Transform(currentScreenPoint, viewportMatrix);

		Novice::DrawLine(static_cast<int>(previousScreenPoint.x), static_cast<int>(previousScreenPoint.y),
			static_cast<int>(currentScreenPoint.x), static_cast<int>(currentScreenPoint.y), color);

		previousPoint = currentPoint;
	}
	
}
