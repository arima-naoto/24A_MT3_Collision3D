#pragma region 
#include "project/math/Pipeline/Rendering.h"

class OBB : public Rendering {

public:

	OBB() = default;

	~OBB() = default;

	void Initialize();

	void Draw(const Vector3 &rotate,OrientedBox& obb,const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void Create_RotateMatrix(const Vector3& rotate, OrientedBox& obb);

	void Create_Vertices(Vector3 vertices[8], OrientedBox& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	Matrix4x4 GetWorldMatrix() { return this->worldMatrix_; }

private:

	Matrix4x4 rotateMatrix;

	Vector3 vertices_[8];

	Matrix4x4 worldMatrix_;

};


