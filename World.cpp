#include "World.h"


/// 初期化処理
World::World(Affine affine) 
{
#pragma region 定義しなければならない

	//アフィン構造体
	affine_ = affine;

	//ワールド行列
	worldMatrix_ = {};

#pragma endregion

}

/// delete処理
World::~World(){}

/// アフィン行列を作成する
void World::MakeAffineMatrix(Affine affine)
{
	//Mathsクラスからメンバ関数AffineMatrixを呼び出す
	worldMatrix_ = Maths::SRTAffineMatrix(affine);
}
