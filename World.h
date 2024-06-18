#pragma once
#include "Maths.h"

/// Mathsクラスを継承したWorldクラスを作成
class World : public Maths
{
public://メンバ関数

	/// インストラクタ
	World(Affine affine);

	/// デストラクタ
	~World();

	/// アフィン行列
	void MakeAffineMatrix(Affine affine);

	/// ワールドビュープロプロジェクション行列
	void MakeWorldViewProjectionMatrix(const Matrix4x4 &viewMatrix,const Matrix4x4& projectionMatrix);

public:

	/// ビュープロジェクション行列のゲッター
	Matrix4x4 GetViewProjectionMatrix();

private://メンバ変数

	//アフィン構造体
	Affine affine_;

	//ワールド行列
	Matrix4x4 worldMatrix_;

	//ワールドビュープロジェクション行列
	Matrix4x4 worldViewprojectioinMatrix_;
};


