#include <Novice.h>
#include "project/Game.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	unique_ptr<Game> game = make_unique<Game>();
	game->Initialize();

	game->Main();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
