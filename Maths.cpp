#define  NOMINMAX
#include "Maths.h"
#include <Novice.h>
using namespace std;

// 関数cotの作成
float Maths::cot(float x)
{
	return 1.0f / tanf(x);
}

Vector3 Maths::Perpendicular(const Vector3& vector) {

	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y ,vector.x,0.0f };
	}

	return { 0.0,-vector.z,vector.y };

}

#pragma region 計算メンバ関数の定義

///加算
Vector3 Maths::Add(const Vector3& v1, const Vector3& v2)
{
	//加算の計算結果を求める
	return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };;
}

///減算
Vector3 Maths::Subtract(const Vector3& v1, const Vector3& v2)
{
	//減算の計算結果を求める
	return { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

///乗算
Vector3 Maths::Multiply(float scalar, const Vector3& v2) {

	//乗算の計算結果を求める
	return { scalar * v2.x ,scalar * v2.y,scalar * v2.z };

}

//内積
float Maths::Dot(const Vector3& v1, const Vector3& v2) {
	//内積を求める
	return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
}

///長さ(ノルム)
float Maths::Length(const Vector3& v) {

	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return result;

}

///正規化
Vector3 Maths::Normalize(const Vector3& v)
{
	//正規化を使用して計算結果を求める
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	Vector3 resultNormalize = { v.x,v.y,v.z };

	if (length != 0.0f)
	{
		resultNormalize = { v.x / length,v.y / length,v.z / length };
	}
	return resultNormalize;
}

//クロス積
Vector3 Maths::Cross(const Vector3& v1, const Vector3& v2)
{
	//クロス積を求める
	Vector3 resultCross = {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};

	return resultCross;
}

#pragma endregion

#pragma region 4x4行列メンバ関数の定義

// 行列の積
Matrix4x4 Maths::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 MultiplyMatrix{};

	//for分を使用して、行列の積を求める
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MultiplyMatrix.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				MultiplyMatrix.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return MultiplyMatrix;
}

// 拡大縮小行列
Matrix4x4 Maths::MakeScaleMatrix(const Vector3& scale)
{
	
	Matrix4x4 resultScale = {
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return resultScale;
}

// X軸回転行列
Matrix4x4 Maths::MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotateXMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cosf(radian),sinf(radian),0.0f,
		0.0f,-sinf(radian),cosf(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateXMatrix;
}

// Y軸回転行列
Matrix4x4 Maths::MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotateYMatrix = {
		cosf(radian),0.0f,-sinf(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sinf(radian),0.0f,cosf(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateYMatrix;
}

// Z軸回転行列
Matrix4x4 Maths::MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotateZMatrix = {
		cosf(radian),sinf(radian),0.0f,0.0f,
		-sinf(radian),cosf(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateZMatrix;
}

// 回転行列
Matrix4x4 Maths::MakeRotateMatrix(const Vector3& radian)
{
	//行列の積を使用して、X軸・Y軸・Z軸回転行列を結合する
	return Multiply(MakeRotateXMatrix(radian.x), Multiply(MakeRotateYMatrix(radian.y), MakeRotateZMatrix(radian.z)));
}

// 平行移動行列
Matrix4x4 Maths::MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 resultTranslate = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x,translate.y,translate.z,1.0f
	};

	return resultTranslate;
}

// アフィン変換行列
Matrix4x4 Maths::AffineMatrix(const Affine&affine)
{
	//行列の積を使用し、拡大縮小行列・回転行列・平行移動行列を結合する
	return Multiply(Multiply(MakeScaleMatrix(affine.scale),MakeRotateMatrix(affine.rotate)),MakeTranslateMatrix(affine.translate));
}

// 逆行列
Matrix4x4 Maths::Inverse(const Matrix4x4 &m)
{
#pragma region //4x4行列の行列式Aを求める
	float MatrixA = 1.0f / (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -
		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -
		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);
#pragma endregion

	Matrix4x4 result;

#pragma region 0行目の逆行列を求める

	result.m[0][0] = MatrixA * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] -
		m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][1] = MatrixA * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][2] = MatrixA * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);

	result.m[0][3] = MatrixA * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);

#pragma endregion

#pragma region 1行目の逆行列を求める

	result.m[1][0] = MatrixA * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] +
		m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);

	result.m[1][1] = MatrixA * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] -
		m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);

	result.m[1][2] = MatrixA * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] +
		m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);

	result.m[1][3] = MatrixA * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] -
		m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);

#pragma endregion

#pragma region 2行目の逆行列を求める

	result.m[2][0] = MatrixA * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] -
		m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][1] = MatrixA * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][2] = MatrixA * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] -
		m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);

	result.m[2][3] = MatrixA * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

#pragma endregion

#pragma region 3行目の逆行列を求める

	result.m[3][0] = MatrixA * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] +
		m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][1] = MatrixA * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][2] = MatrixA * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] +
		m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);

	result.m[3][3] = MatrixA * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);


#pragma endregion 

	return result;

}

// 透視投影行列
Matrix4x4 Maths::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 resultPerspectiveFov = {
		1.0f / aspectRatio * cot(fovY / 2.0f),0.0f,0.0f,0.0f,
		0.0f,cot(fovY / 2.0f),0.0f,0.0f,
		0.0f,0.0f,farClip / (farClip - nearClip),1.0f,
		0.0f,0.0f,-(nearClip * farClip) / (farClip - nearClip),0.0f
	};

	return resultPerspectiveFov;
}

// ビューポート変換行列
Matrix4x4 Maths::ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 resultViewport = {
		width / 2.0f,0.0f,0.0f,0.0f,
		0.0f,-height / 2.0f,0.0f,0.0f,
		0.0f,0.0f,maxDepth - minDepth,0.0f,
		(left + width) / 2.0f,(top + height) / 2.0f,minDepth,1.0f
	};

	return resultViewport;
}

#pragma endregion

// 座標変換
Vector3 Maths::Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

///線分と三角形の衝突判定
bool Maths::IsCollision(const Triangle& triangle,const Segment& segment) {

	//三角形の頂点
	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	//三角形の辺のベクトルを計算
	Vector3 v01 = Maths::Subtract(v1, v0);
	Vector3 v12 = Maths::Subtract(v2, v1);
	Vector3 v20 = Maths::Subtract(v0, v2);

	//三角形の法線ベクトルを計算
	Vector3 normal = Maths::Normalize(Maths::Cross(v01, v12));

	//線分の始点と終点のベクトルを計算
	Vector3 end = Maths::Add(segment.origin, segment.diff);
	Vector3 v1p = Maths::Subtract(end, v0);
	Vector3 v2p = Maths::Subtract(end, v1);
	Vector3 v0p = Maths::Subtract(end, v2);

	//各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
	Vector3 cross01 = Maths::Cross(v01, v1p);
	Vector3 cross12 = Maths::Cross(v12, v2p);
	Vector3 cross20 = Maths::Cross(v20, v0p);

	//全ての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Maths::Dot(cross01, normal) >= 0.0f &&
		Maths::Dot(cross12, normal) >= 0.0f &&
		Maths::Dot(cross20, normal) >= 0.0f) {
		return true;
	}

	return false;
}



