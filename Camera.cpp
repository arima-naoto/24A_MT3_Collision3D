#include "Camera.h"

/// 初期化処理
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

/// delete処理
Camera::~Camera(){}

/// アフィン行列の作成
void Camera::MakeAffineMatrix(Affine affine)
{
	//Mathsクラスからメンバ関数AffinnMatrixを呼び出す
	cameraWorldMatrix_ = Maths::AffineMatrix(affine);
}

/// ビュー行列の作成
void Camera::MakeViewMatrix() 
{
	//Mathsクラスからメンバ関数Inverseを呼び出す
	viewMatrix_ = Maths::Inverse(cameraWorldMatrix_);
}

/// プロジェクション行列の作成
void Camera::MakeProjectionMatrix() 
{
	//Mathクラスからメンバ関数MakePerspectiveFovMatrixを呼び出す
	projectionMatrix_ = Maths::MakePerspectiveFovMatrix(0.45f, kWindowWidth_ / kWindowHeight_, 0.1f, 100.0f);
}

/// ビューポート行列の作成
void Camera::MakeViewportMatrix() 
{
	//MathsクラスからViewportを呼び出す
	viewportMatrix_ = Maths::ViewportMatrix(0, 0, kWindowWidth_, kWindowHeight_, 0.0f, 1.0f);
}

/// ビュー行列のゲッターの戻り値を設定する
Matrix4x4 Camera::GetViewMatrix() { return viewMatrix_; }

/// プロジェクション行列のゲッターの戻り値を設定する
Matrix4x4 Camera::GetProjectionMatrix() { return projectionMatrix_; }

/// ビューポート行列のゲッターの戻り値を設定する
Matrix4x4 Camera::GetViewportMatrix() { return viewportMatrix_; }

/// 画面横幅のゲッターの戻り値を設定する
float Camera::GetKWindowWidth() { return kWindowWidth_; }

/// 画面縦幅のゲッターの戻り値を設定する
float Camera::GetKWindowHeight() { return kWindowHeight_; }