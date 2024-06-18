#include <Novice.h>
#include <Game.h>

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//Gameクラスのインスタンスの作成
	Game* game = new Game();

	//処理を一つにまとめたGameクラスのメンバ関数Mainを呼び出す
	game->Main();

	// ライブラリの終了
	Novice::Finalize();
	delete game;
	return 0;
}
