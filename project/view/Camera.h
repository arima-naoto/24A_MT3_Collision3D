#pragma once
#include "project/math/Pipeline/Rendering.h"

class Camera : public Rendering {

public://メンバ関数

	Camera() = default;

	~Camera() = default;

	void Initialize(Affine affine);

	void CreateCameraMatrix(Affine affine);

	void CreateViewMatrix();

	void CreateProjectionMatrix();

	void CreateViewProjectionMatrix();

	void CreateViewportMatrix();

public:

	Matrix4x4 GetViewProjectionMatrix();

	Matrix4x4 GetViewportMatrix();

	static inline const float kWindowWidth_ = 1280.0f;
	static inline const float kWindowHeight_ = 720.0f;

private:

	Affine affine_;

	Fov<float> perspective_;

	ViewRect<float> viewport_;

	Matrix4x4 cameraMatrix_;

	Matrix4x4 viewMatrix_;

	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectionMatrix_;

	Matrix4x4 viewportMatrix_;

};

