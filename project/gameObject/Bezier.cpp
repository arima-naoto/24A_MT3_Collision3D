#include "Bezier.h"

Vector3 Bezier::Lerp(const Vector3& v1, const Vector3& v2, float t) { return Vector3(v1 * (1.0f - t) + v2 * t); }

void Bezier::Draw(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, 
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){

	int segments = 32; // ベジエ曲線を分割するセグメント数
	Vector3 previousPoint = Transform(controlPoint0, viewProjectionMatrix);
	previousPoint = Transform(previousPoint, viewportMatrix);

	for (int i = 1; i <= segments; i++) {
		float t = static_cast<float>(i) / static_cast<float>(segments);

		// ベジエ曲線の各点を計算
		Vector3 p0p1 = Lerp(controlPoint0, controlPoint1, t);
		Vector3 p1p2 = Lerp(controlPoint1, controlPoint2, t);
		Vector3 currentPoint = Lerp(p0p1, p1p2, t);

		currentPoint = Transform(currentPoint, viewProjectionMatrix);
		currentPoint = Transform(currentPoint, viewportMatrix);

		// 座標を整数に変換して線を描画
		Novice::DrawLine(static_cast<int>(previousPoint.x), static_cast<int>(previousPoint.y),
			static_cast<int>(currentPoint.x), static_cast<int>(currentPoint.y),
			color);

		// 現在の点を次の線の始点として設定
		previousPoint = currentPoint;
	}

}
