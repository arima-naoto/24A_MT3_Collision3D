#include "Camera.h"

void Camera::Initialize(Affine affine) {

	affine_ = affine;

	perspective_ = {
		.fovY = .45f,
		.aspectRatio = Camera::kWindowWidth_ / Camera::kWindowHeight_,
		.nearClip = .1f,
		.farClip = 100
	};

	viewport_ = {
		.left = 0,
		.top = 0,
		.width = Camera::kWindowWidth_,
		.height = Camera::kWindowHeight_,
		.minDepth = 0,
		.maxDepth = 1,
	};

	cameraMatrix_ = {};
	viewMatrix_ = {};
	projectionMatrix_ = {};
	viewProjectionMatrix_ = {};
	viewportMatrix_ = {};
}

void Camera::CreateCameraMatrix(Affine affine) { cameraMatrix_ = STRAffineMatrix(affine); }

void Camera::CreateViewMatrix() { viewMatrix_ = Inverse(cameraMatrix_); }

void Camera::CreateProjectionMatrix() { projectionMatrix_ = MakePerspectiveFovMatrix(perspective_); }

void Camera::CreateViewProjectionMatrix() { viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_; }

void Camera::CreateViewportMatrix() { viewportMatrix_ = ViewportMatrix(viewport_); }

Matrix4x4 Camera::GetViewProjectionMatrix() { return viewProjectionMatrix_; }

Matrix4x4 Camera::GetViewportMatrix() { return viewportMatrix_; }