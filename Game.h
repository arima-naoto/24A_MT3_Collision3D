#pragma once
#include "World.h"
#include "Camera.h"
#include "Maths.h"

/// <summary>
/// Mathsクラスを継承したGameクラスを作成
/// </summary>
class Game : public Maths
{
public://メンバ関数

	/// <summary>
	/// インストラクタ
	/// </summary>
	Game();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Game();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// デバッグテキスト描画メンバ関数
	/// </summary>
	void DrawDebugText();

	/// <summary>
	/// グリッド線描画メンバ関数
	/// </summary>
	/// <param name="viewProjectionMatrix">ビュープロジェクション行列</param>
	/// <param name="viewportMatrix">ビューポート行列</param>
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color);

	/// <summary>
	/// 球体描画メンバ関数
	/// </summary>
	/// <param name="sphere">球体</param>
	/// <param name="viewProjectionMatrix">ビュープロジェクション行列</param>
	/// <param name="viewportMatrix">ビューポート行列</param>
	/// <param name="color">描画する色</param>
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 処理を一つにまとめるメンバ関数
	/// </summary>
	void Main();


private://メンバ変数

	//ワールドアフィン
	Affine worldAffine_;

	//ワールドクラス
	World* world_;

	//カメラアフィン
	Affine cameraAffine_;

	//カメラクラス
	Camera* camera_;

	//配列型Sphere構造体
	Sphere sphere_[2];

	//スフィアを描画する色
	uint32_t sphereColor_[2];
};

