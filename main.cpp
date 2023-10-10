#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include <Function.h>

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Player player = {
		{0,0},
		{0,0},
		{0,0},
		true,
		3
	};

	float theta = 0.0f;
	float thetaCount = 0.0f;
	float thetaCountAdd = 0.1f;

	bool isDirectionMater = true;
	bool isSpeedMater = false;

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
		
		//プレイヤー
		if (isDirectionMater == true) {
			thetaCount += thetaCountAdd;
			if (thetaCount > 0.4f || thetaCount < -0.4f) {
				thetaCountAdd *= -1;
			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
