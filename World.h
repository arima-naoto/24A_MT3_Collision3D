#pragma once
#include "Maths.h"

/// <summary>
/// Mathsクラスを継承したWorldクラスを作成
/// </summary>
class World : public Maths
{
public://メンバ関数

	/// <summary>
	/// インストラクタ
	/// </summary>
	/// <param name="affine">アフィン構造体</param>
	World(Affine affine);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~World();

	/// <summary>
	/// アフィン行列
	/// </summary>
	/// <param name="affine">アフィン構造体</param>
	void MakeAffineMatrix(Affine affine);

	/// <summary>
	/// ワールドビュープロプロジェクション行列
	/// </summary>
	/// <param name="viewMatrix">ビュー行列</param>
	/// <param name="projectionMatrix">プロジェクション行列</param>
	void MakeWorldViewProjectionMatrix(const Matrix4x4 &viewMatrix,const Matrix4x4& projectionMatrix);

public:

	/// <summary>
	/// ビュープロジェクション行列のゲッター
	/// </summary>
	/// <returns></returns>
	Matrix4x4 GetViewProjectionMatrix();

private://メンバ変数

	//アフィン構造体
	Affine affine_;

	//ワールド行列
	Matrix4x4 worldMatrix_;

	//ワールドビュープロジェクション行列
	Matrix4x4 worldViewprojectioinMatrix_;
};


