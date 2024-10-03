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

private://メンバ変数

	//アフィン構造体
	Affine affine_;

	//ワールド行列
	Matrix4x4 worldMatrix_;

};


