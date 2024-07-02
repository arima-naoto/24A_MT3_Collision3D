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

	/// インストラクタ
	Game();

	/// デストラクタ
	~Game();

	///ゲームタイトル
	void Title();

	/// レンダリングパイプライン
	void Rendering();

	///衝突判定メンバ関数
	void CheckIsCollision();

	/// 更新処理
	void Update();

	/// デバッグテキスト描画メンバ関数
	void DrawDebugText();

	/// グリッド線描画メンバ関数
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color);

	/// 球体描画メンバ関数
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	///平面描画メンバ関数
	void DrawPlane(const Plane& plane, Matrix4x4 viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	///三角形描画メンバ関数
	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	///AABB描画メンバ関数
	void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	/// 描画処理
	void Draw();

	/// 処理を一つにまとめるメンバ関数
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

	///AABB構造体
	AABB aabb_[2];

	///AABBを描画する色
	uint32_t aabbColor_[2];


};

