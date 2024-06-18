#include "World.h"


/// 初期化処理
World::World(Affine affine) 
{
#pragma region 定義しなければならない

	//アフィン構造体
	affine_ = affine;

	//ワールド行列
	worldMatrix_ = {};

	//ワールドビュープロジェクション行列
	worldViewprojectioinMatrix_ = {};

#pragma endregion

}

/// delete処理
World::~World(){}

/// アフィン行列を作成する
void World::MakeAffineMatrix(Affine affine)
{
	//Mathsクラスからメンバ関数AffineMatrixを呼び出す
	worldMatrix_ = Maths::AffineMatrix(affine);
}

/// ビュープロジェクション行列を作成する
void World::MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix,const Matrix4x4& projectionMatrix) 
{
	//Mathsクラスからメンバ関数Multiplyを呼び出す
	worldViewprojectioinMatrix_ = Maths::Multiply(worldMatrix_, Maths::Multiply(viewMatrix, projectionMatrix));
}

/// ビュープロジェクション行列のゲッターの戻り値を設定する
Matrix4x4 World::GetViewProjectionMatrix() { return worldViewprojectioinMatrix_; }
