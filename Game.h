#pragma once
#include "World.h"
#include "Camera.h"
#include "Maths.h"
#include "Vector2.h"

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

	/// 球体同士の衝突判定
	void SphereIsColllsion();

	///	カメラ拡大縮小メンバ関数
	void MoveScale();

	/// カメラ回転メンバ関数
	void MoveRotation(char *keys);

	/// カメラ移動メンバ関数
	void MoveTranslate(char* keys);

	///カメラ操作
	void CameraOperator(char *keys);

	/// 更新処理
	void Update(char *keys);

	/// デバッグテキスト描画メンバ関数
	void DrawDebugText();

	/// グリッド線描画メンバ関数
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color);

	/// 球体描画メンバ関数
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

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

	///回転速度
	float rotateSpeed_;

	//移動速度
	Vector2 translateSpeed_;

	//カメラクラス
	Camera* camera_;

	//配列型Sphere構造体
	Sphere sphere_[2];

	//スフィアを描画する色
	uint32_t sphereColor_[2];


};

