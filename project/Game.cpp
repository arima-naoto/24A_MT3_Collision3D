#define NOMINMAX
#include "Game.h"
#include "IsCollision.h"
#include "string"

#include "algorithm"
#ifdef _DEBUG
#include "imgui.h"
using namespace ImGui;
#endif // _DEBUG




void Game::Initialize() {

	Create_Unique();

	// ワールド
	affine_[GameView::kWorld] = {
		.scale{1,1,1},
		.rotate{0,0,0},
		.translate{0,0,0}
	};

	// カメラ
	affine_[GameView::kCamera] = {
		.scale{ 1.0f,1.0f,1.0f },
		.rotate{ 0.26f,0.0f,0.0f },
		.translate{ 0.0f,0.2f,-6.77f }
	};

	rotate_ = {};

	segment_ = {
		.origin{-0.8f,-0.3f,0.0f},
		.diff{0.5f,0.5f,0.5f}
	};

	obb = {
		.center{-1.0f,0.0f,0.0f},
		.orientations{
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}},
		.size{0.5f,0.5f,0.5f}
	};

	obbColor = WHITE;

}

void Game::Update(){

	///
	/// ↓更新処理ここから
	///

	//レンダリングパイプライン作成
	Create_Pipeline();

	///カメラの拡大縮小処理
	CameraMoveScale(affine_[GameView::kCamera]);

	///カメラの回転処理
	CameraMoveRotate(affine_[GameView::kCamera]);


	CheckCollision();

	///
	/// ↑更新処理ここまで
	///
}

void Game::Draw(){

	///
    /// ↓描画処理ここから
    ///

	//デバッグテキストを描画
	Game::DrawDebugText();

	//グリッド線を描画
	grid_->Draw(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), uint32_t(ObjectColor::kGrid));

	Game::DrawSegment();

	//OBBを描画
	obb_->Draw(rotate_, obb, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), obbColor);


	///
	/// ↑描画処理ここまで
	///

}

void Game::Create_Unique() {

	world_ = make_unique<World>();
	world_->Initailize(affine_[GameView::kWorld]);

	camera_ = make_unique<Camera>();
	camera_->Initialize(affine_[GameView::kCamera]);

	sphere_ = make_unique<Sphere>();

	grid_ = make_unique<Grid>();

	obb_ = make_unique<OBB>();
	obb_->Initialize();

}

void Game::Create_Pipeline() {

	///ワールド行列
	world_->CreateWorldMatrix(affine_[GameView::kWorld]);

	///カメラワールド行列
	camera_->CreateCameraMatrix(affine_[GameView::kCamera]);

	///ビュー行列
	camera_->CreateViewMatrix();

	///プロジェクション行列
	camera_->CreateProjectionMatrix();

	///ビュープロジェクション行列
	camera_->CreateViewProjectionMatrix();

	///ビューポート行列
	camera_->CreateViewportMatrix();

}

void Game::CameraMoveScale(Affine& camera){

	int32_t wheelScroll = Novice::GetWheel();

	//スクロール量の最小値と最大値
	float scroll[2] = { 0.5f,1.0f };

	if (wheelScroll != 0) {
		camera.scale.z -= (wheelScroll / (1024.f * 2));
		camera.scale.z = std::clamp(camera.scale.z, scroll[0], scroll[1]);
	}

}

void Game::CameraMoveRotate(Affine& camera) {

	static Vector2 prevMouse = { 0,0 };
	static Vector2 mouse = { 0,0 };

	Novice::GetMousePosition(&mouse.x, &mouse.y);
	
	int mouseClickLeft = 1;

	if (Novice::IsPressMouse(mouseClickLeft)) {
		Vector2 delta = mouse - prevMouse;
		camera.rotate.x += delta.y * 0.0025f;
		camera.rotate.y += delta.x * 0.0025f;
	}

	prevMouse = mouse;

}

void Game::CheckCollision() {

	Matrix4x4 obbInverse = Inverse(obb_->GetWorldMatrix());

	Vector3 localOrigin = Transform(segment_.origin,obbInverse);
	Vector3 localEnd = Transform(segment_.origin + segment_.diff, obbInverse);

	AlignedBox localAABB{
		{-obb.size.x,-obb.size.y,-obb.size.z},
		{obb.size.x,obb.size.y,obb.size.z},
	};

	Segment localSegment;
	localSegment.origin = localOrigin;
	localSegment.diff = localEnd - localOrigin;

	if (IsCollision(localAABB, localSegment)) {
		obbColor = RED;
	}
	else {
		obbColor = WHITE;
	}


}

void Game::DrawDebugText() {
	DragFloat3("obb.center", &obb.center.x, 0.01f);
	SliderFloat("rotateX", &rotate_.x, 0.0f, 1.59f);
	SliderFloat("rotateY", &rotate_.y, 0.0f, 1.59f);
	SliderFloat("rotateZ", &rotate_.z, 0.0f, 1.59f);
}

void Game::DrawSegment() {

	Vector3 axisStart = Transform(Transform(segment_.origin, camera_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());

	Vector3 axisEnd = Transform(Transform(Add(segment_.origin, segment_.diff), camera_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());

	Novice::DrawLine((int)axisStart.x, (int)axisStart.y, (int)axisEnd.x, (int)axisEnd.y, uint32_t(ObjectColor::kSegment));



}

void Game::Setting_WindowSize() {

	const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

	//画面の横幅、縦幅
	int windowWidth = static_cast<int32_t>(Camera::kWindowWidth_);
	int windowHeight = static_cast<int32_t>(Camera::kWindowHeight_);

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, windowWidth, windowHeight);

}

void Game::StartFrame(char* keys, char* preKeys) {

	// フレームの開始
	Novice::BeginFrame();

	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	// 更新処理
	Game::Update();

	// 描画処理
	Game::Draw();

}

void Game::Loop(char* keys, char* preKeys) {

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {

		//フレームのスタート
		Game::StartFrame(keys, preKeys);

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

}

void Game::Main() {

	Game::Setting_WindowSize();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Game::Loop(keys, preKeys);

}