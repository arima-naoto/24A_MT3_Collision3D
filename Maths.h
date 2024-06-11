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

	///メンバ関数Lengthの宣言
	static float Length(const Vector3& v);

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

	/// 座標変換
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="s1"></param>
	/// <param name="s2"></param>
	/// <returns></returns>
	static bool IsCollision(const Sphere& s1, const Sphere& s2);

};
