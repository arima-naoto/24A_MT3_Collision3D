#pragma once
#include "project/math/Pipeline/Rendering.h"
#include "project/view/World.h"
#include "project/view/Camera.h"
#include "project/gameObject/Sphere.h"
#include "project/gameObject/Grid.h"
#include "project/gameObject/OBB.h"

#include "memory"
using namespace std;

#define GRAY 0xAAAAAAFF

enum GameView {
	kWorld,
	kCamera
};

enum ObjectColor {
	kGrid = GRAY,
	kSphere = BLACK,
	kSegment = WHITE,
};

class Game : public Rendering{

public:

	Game() = default;

	~Game() = default;

	void Initialize();

	void Update();

	void Draw();

	void Create_Unique();

	void Create_Pipeline();

	void CameraMoveScale(Affine& camera);

	void CameraMoveRotate(Affine& camera);

	void CheckCollision();

	void DrawDebugText();

	void DrawSegment();

	void Setting_WindowSize();

	void StartFrame(char *keys,char *preKeys);

	void Loop(char* keys, char* preKeys);

	void Main();


private:

	unique_ptr<World> world_ = nullptr;
	unique_ptr<Camera> camera_ = nullptr;

	unique_ptr<Sphere> sphere_ = nullptr;
	unique_ptr<Grid> grid_ = nullptr;
	unique_ptr<OBB> obb_ = nullptr;

	Affine affine_[2];

	Vector3 rotate_;

	Segment segment_;
	OrientedBox obb;

	uint32_t obbColor;

};

