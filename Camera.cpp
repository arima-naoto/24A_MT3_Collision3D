#include "Camera.h"

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="affine">アフィン構造体</param>
Camera::Camera(Affine affine) 
{
#pragma region 定義しなければならない

	//アフィン構造体
	affine_ = affine;

	//カメラワールド行列
	cameraWorldMatrix_ = {};

	//ビュー行列
	viewMatrix_ = {};

	//プロジェクション行列
	projectionMatrix_ = {};

	//ビューポート行列
	viewportMatrix_ = {};

#pragma endregion
}

/// <summary>
/// delete処理
/// </summary>
Camera::~Camera(){}

/// <summary>
/// アフィン行列の作成
/// </summary>
/// <param name="affine">アフィン構造体</param>
void Camera::MakeAffineMatrix(Affine affine) 
{
	//Mathsクラスからメンバ関数AffinnMatrixを呼び出す
	cameraWorldMatrix_ = Maths::AffineMatrix(affine);
}

/// <summary>
/// ビュー行列の作成
/// </summary>
void Camera::MakeViewMatrix() 
{
	//Mathsクラスからメンバ関数Inverseを呼び出す
	viewMatrix_ = Maths::Inverse(cameraWorldMatrix_);
}

/// <summary>
/// プロジェクション行列の作成
/// </summary>
void Camera::MakeProjectionMatrix() 
{
	//Mathクラスからメンバ関数MakePerspectiveFovMatrixを呼び出す
	projectionMatrix_ = Maths::MakePerspectiveFovMatrix(0.45f, kWindowWidth_ / kWindowHeight_, 0.1f, 100.0f);
}

/// <summary>
/// ビューポート行列の作成
/// </summary>
void Camera::MakeViewportMatrix() 
{
	//MathsクラスからViewportを呼び出す
	viewportMatrix_ = Maths::ViewportMatrix(0, 0, kWindowWidth_, kWindowHeight_, 0.0f, 1.0f);
}

/// <summary>
/// ビュー行列のゲッターの戻り値を設定する
/// </summary>
/// <returns></returns>
Matrix4x4 Camera::GetViewMatrix() { return viewMatrix_; }

/// <summary>
/// プロジェクション行列のゲッターの戻り値を設定する
/// </summary>
/// <returns></returns>
Matrix4x4 Camera::GetProjectionMatrix() { return projectionMatrix_; }

/// <summary>
/// ビューポート行列のゲッターの戻り値を設定する
/// </summary>
/// <returns></returns>
Matrix4x4 Camera::GetViewportMatrix() { return viewportMatrix_; }

/// <summary>
/// 画面横幅のゲッターの戻り値を設定する
/// </summary>
/// <returns></returns>
float Camera::GetKWindowWidth() { return kWindowWidth_; }

/// <summary>
/// 画面縦幅のゲッターの戻り値を設定する
/// </summary>
/// <returns></returns>
float Camera::GetKWindowHeight() { return kWindowHeight_; }