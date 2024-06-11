#include <Novice.h>
#include <Game.h>
#include <Camera.h>

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetKWindowWidth(), (int)Camera::GetKWindowHeight());


	//Gameクラスのインスタンスの作成
	Game* game = new Game();

	//処理を一つにまとめたGameクラスのメンバ関数Mainを呼び出す
	game->Main();

	// ライブラリの終了
	Novice::Finalize();
	delete game;
	return 0;
}
