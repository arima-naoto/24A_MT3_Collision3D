#include "World.h"

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="affine">アフィン構造体</param>
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

/// <summary>
/// delete処理
/// </summary>
World::~World(){}

/// <summary>
/// アフィン行列を作成する
/// </summary>
/// <param name="affine"></param>
void World::MakeAffineMatrix(Affine affine) 
{
	//Mathsクラスからメンバ関数AffineMatrixを呼び出す
	worldMatrix_ = Maths::AffineMatrix(affine);
}

/// <summary>
/// ビュープロジェクション行列を作成する
/// </summary>
/// <param name="viewMatrix"></param>
/// <param name="projectionMatrix"></param>
void World::MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix,const Matrix4x4& projectionMatrix) 
{
	//Mathsクラスからメンバ関数Multiplyを呼び出す
	worldViewprojectioinMatrix_ = Maths::Multiply(worldMatrix_, Maths::Multiply(viewMatrix, projectionMatrix));
}

/// <summary>
/// ビュープロジェクション行列のゲッターの戻り値を設定する
/// </summary>
/// <returns></returns>
Matrix4x4 World::GetViewProjectionMatrix() { return worldViewprojectioinMatrix_; }
