#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Struct.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

/// <summary>
/// Mathsクラスの作成
/// </summary>
class Maths 
{
public://メンバ関数

	static float cot(float x);

	static Vector3 Perpendicular(const Vector3& vector);

#pragma region 計算メンバ関数の宣言

	///加算
	static Vector3 Add(const Vector3& v1, const Vector3& v2);

	///減算
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	///乗算
	static Vector3 Multiply(float scalar, const Vector3& v2);

	///内積
	static float Dot(const Vector3& v1, const Vector3& v2);

	///長さ(ノルム)
	static float Length(const Vector3& v);

	///正規化
	static Vector3 Normalize(const Vector3& v);

	///クロス積
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

#pragma endregion

#pragma region 4x4行列メンバ関数の宣言

	/// 行列の積
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// 拡大縮小行列
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// X軸回転行列
	static Matrix4x4 MakeRotateXMatrix(float radian);

	/// Y軸回転行列
	static Matrix4x4 MakeRotateYMatrix(float radian);

	/// Z軸回転行列
	static Matrix4x4 MakeRotateZMatrix(float radian);

	/// 回転行列
	static Matrix4x4 MakeRotateMatrix(const Vector3& radian);

	/// 平行移動行列 
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// アフィン変換行列
	static Matrix4x4 AffineMatrix(const Affine& affine);

	/// 逆行列
	static Matrix4x4 Inverse(const Matrix4x4& m);

	/// 透視投影行列
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// ビューポート変換行列
	static Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

#pragma endregion

	/// 座標変換
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// 線分と三角形の衝突判定
	static bool IsCollision(const Triangle& triangle, const Segment& segment);

};
