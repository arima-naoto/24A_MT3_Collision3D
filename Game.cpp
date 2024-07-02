#include "Game.h"
#include <Novice.h>
#include <imgui.h>
#define GRAY 0xAAAAAAFF //色を作成

/// 初期化処理
Game::Game() 
{
#pragma region 定義しなければならない

	//ワールドアフィン
	worldAffine_ = {
		{1.0f,1.0f,1.0f},
		{0,0,0},
		{0,0,0},
	};

	//ワールドクラスのインスタンスを作成
	world_ = new World(worldAffine_);

	//カメラアフィン
	cameraAffine_ = {
		{ 1.0f,1.0f,1.0f },
		{ 0.26f,0.0f,0.0f },
		{ 0.0f,1.9f,-6.49f }
	};

	//回転速度
	rotateSpeed_ = 0.005f;

	///移動速度
	translateSpeed_ = { 0.01f,0.01f };

	//カメラクラスのインスタンスを作成
	camera_ = new Camera(cameraAffine_);

	sphere_ = {
		{0.12f,0.0f,0.0f},
		0.6f
	};

	///スフィアを描画する色
	sphereColor_ = WHITE;
	


#pragma endregion
}

/// delete処理
Game::~Game() 
{
	delete world_, camera_;
}

//ゲームタイトル
void Game::Title() {

	//ウィンドウバーの名前
	const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetKWindowWidth(), (int)Camera::GetKWindowHeight());
}

/// レンダリングパイプラインの作成
void Game::Rendering() 
{
	//ワールド行列
	world_->MakeAffineMatrix(worldAffine_);

	//カメラワールド行列
	camera_->MakeAffineMatrix(cameraAffine_);

	//ビュー行列
	camera_->MakeViewMatrix();

	//プロジェクション行列
	camera_->MakeProjectionMatrix();

	//ワールドビュープロジェクション行列
	world_->MakeWorldViewProjectionMatrix(camera_->GetViewMatrix(), camera_->GetProjectionMatrix());

	//ビューポート行列
	camera_->MakeViewportMatrix();
}


/// 更新処理
void Game::Update()
{
	//レンダリングパイプライン
	Game::Rendering();
}

/// デバッグテキストの描画
void Game::DrawDebugText() 
{
	///デバッグテキストの描画
	ImGui::Begin("DebugWindow");
	ImGui::DragFloat3("sphere[0] center", &sphere_.center.x, 0.01f);
	ImGui::DragFloat("sphere[0] radius", &sphere_.radius, 0.01f);
	ImGui::End();
}

/// グリッド描画処理
void Game::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color)
{
	const float kGirdHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGirdEvery = (kGirdHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float positionX = -kGirdHalfWidth + (xIndex * kGirdEvery);

		// 奥から手前への線
		Vector3 start = { positionX, 0.0f, -kGirdHalfWidth };
		Vector3 end = { positionX, 0.0f, kGirdHalfWidth };

		// スクリーン座標系まで変換をかける
		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		// ラインの描画
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, positionX == 0.0f ? BLACK : color);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float positionZ = -kGirdHalfWidth + (zIndex * kGirdEvery);

		// 左から右への線
		Vector3 start = { -kGirdHalfWidth, 0.0f, positionZ };
		Vector3 end = { kGirdHalfWidth, 0.0f, positionZ };

		//スクリーン座標系まで変換をかける
		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		// ラインの描画（仮の関数）
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, positionZ == 0.0f ? BLACK : color);
	}
}

/// 球体描画処理
void Game::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{
	const uint32_t kSubdivision = 10; // 分割数
	const float kLonEvery = (2.0f * float(M_PI)) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision; // 緯度分割1つ分の角度

	// 緯度の方向に分割 -π/2～π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; // 現在の緯度
		float nextLat = lat + kLatEvery; // 次の緯度

		// 経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			float nextLon = lon + kLonEvery; // 次の経度

			// ワールド座標系のa, b, cを求める
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(nextLon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(nextLon)
			};

			// ワールド座標系のa, b, cをスクリーン座標系まで変換
			Vector3 ScreenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			// abで線を引く
			Novice::DrawLine((int)ScreenA.x, (int)ScreenA.y, (int)ScreenB.x, (int)ScreenB.y, color);

			// bcで線を引く
			Novice::DrawLine((int)ScreenB.x, (int)ScreenB.y, (int)ScreenC.x, (int)ScreenC.y, color);
		}
	}
}

/// 描画処理(これまで定義した描画処理をDraw関数の中で呼び出す)
void Game::Draw() 
{

	//グリッドを描画する色
	uint32_t gridColor = GRAY;

	//デバッグテキストの描画
	Game::DrawDebugText();

	//グリッド線を描画
	Game::DrawGrid(world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), gridColor);

	//球体描画
	Game::DrawSphere(sphere_, world_->GetViewProjectionMatrix() , camera_->GetViewportMatrix(), sphereColor_);
}

/// Main関数で処理を一つにまとめる
void Game::Main() 
{
	///メンバ関数Titleを呼び出す
	Game::Title();
	
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//更新の処理をまとめたメンバ関数Updateを呼び出す
		Game::Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//描画の処理をまとめたメンバ関数Drawを呼び出す
		Game::Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
}