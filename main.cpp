#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include <Function.h>

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

//ウィンドウサイズ
const int kWindowWideth = 600;
const int kWindowHeight = 720;

//壁の厚さ
int wallSize = 32;

//敵の数とサイズ
const int kEnemyNumS2_1 = 1;
const int kEnemyNumS2_2 = 2;
const int kEnemySize = 64;

//浮島のサイズ
const int kSafeZoneNum1_1 = 2;
const int kSafeZoneNum1_2 = 2;
const int kSafeZoneNum1_3 = 3;

//浮島の大きさ
const float kSafeZoneSizeMin = 48;
const float kSafeZoneSizeMiddle = 64;
const float kSafeZoneSizeBig = 96;

//落とし穴の数
const int kPitFall3_1 = 2;
const int kPitFall3_2 = 3;
const int kPitFall3_3 = 3;

//落とし穴の大きさ
const float kPitFallSizeMin = 48;
const float kPitFallSizeMiddle = 64;
const float kPitFallSizeBig = 96;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWideth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//プレイヤー
	Player player = {
		{300.0f,600.0f},
		{0,0},
		{0,0},
		48,
		true,
		false,
		false,
		3
	};

	//画像
	int playerFrontTexture[4];
	playerFrontTexture[0] = Novice::LoadTexture("./images/daihuku1.png");
	playerFrontTexture[1] = Novice::LoadTexture("./images/daihuku2.png");
	playerFrontTexture[2] = Novice::LoadTexture("./images/daihuku3.png");
	playerFrontTexture[3] = Novice::LoadTexture("./images/daihuku4.png");
	//int playerRightTexture[4];
	//playerRightTexture[0] = Novice::LoadTexture("./images/daihuku1.png");
	//playerRightTexture[1] = Novice::LoadTexture("./images/daihuku2.png");
	//playerRightTexture[2] = Novice::LoadTexture("./images/daihuku3.png");
	//playerRightTexture[3] = Novice::LoadTexture("./images/daihuku4.png");
	//int playerLeftTexture[4];
	//playerLeftTexture[0] = Novice::LoadTexture("./images/daihuku1.png");
	//playerLeftTexture[1] = Novice::LoadTexture("./images/daihuku2.png");
	//playerLeftTexture[2] = Novice::LoadTexture("./images/daihuku3.png");
	//playerLeftTexture[3] = Novice::LoadTexture("./images/daihuku4.png");
	//int playerBackTexture[4];
	//playerBackTexture[0] = Novice::LoadTexture("./images/daihuku_back1.png");
	//playerBackTexture[1] = Novice::LoadTexture("./images/daihuku_back2.png");
	//playerBackTexture[2] = Novice::LoadTexture("./images/daihuku_back3.png");
	//playerBackTexture[3] = Novice::LoadTexture("./images/daihuku_back4.png");

	int enemyTexture[4];
	enemyTexture[0] = Novice::LoadTexture("./images/amechan1.png");
	enemyTexture[1] = Novice::LoadTexture("./images/amechan2.png");
	enemyTexture[2] = Novice::LoadTexture("./images/amechan3.png");
	enemyTexture[3] = Novice::LoadTexture("./images/amechan4.png");

	int safeZoneTexture = Novice::LoadTexture("./images/ukishima.png");

	//シーン
	Scene scene = PLAY;

	Stage stage = S2_1;

	//標準
	//float theta = 0.0f;
	float thetaCount = 0.0f;

	Vector2f aimPosition = { 0,0 };

	float speedCount = 0.6f;
	float speedCountAdd = 0.1f;

	bool isDirectionMater = true;
	bool isSpeedMater = false;

	//浮島
	SafeZone safeZone1_1[kSafeZoneNum1_1];
	safeZone1_1[0] = {
		{280, 330},
		kSafeZoneSizeMin
	};
	safeZone1_1[1] = {
		{100, 100},
		kSafeZoneSizeBig
	};

	SafeZone safeZone1_2[2];
	safeZone1_2[0] = {
	{300, 200},
	kSafeZoneSizeBig
	};
	safeZone1_2[1] = {
	{150, 300},
	kSafeZoneSizeBig
	};

	SafeZone safeZone1_3[3];
	safeZone1_3[0] = {
	{300, 200},
	kSafeZoneSizeBig
	};
	safeZone1_3[1] = {
	{150, 300},
	kSafeZoneSizeBig
	};
	safeZone1_3[2] = {
	{200, 500},
	kSafeZoneSizeBig
	};
	
	//プログラムで使うステージの浮島の数
	int safeZoneNum = kSafeZoneNum1_1;

	//プログラムで使う浮島
	SafeZone safeZone[5] = {};

	//落とし穴
	SafeZone pitFall3_1[kPitFall3_1];
	pitFall3_1[0] = {
		{100,200},
		kPitFallSizeMin
	};
	pitFall3_1[1] = {
		{300,600},
		kPitFallSizeBig
	};

	SafeZone pitFall3_2[kPitFall3_2];
	pitFall3_2[0] = {
		{100,200},
		kPitFallSizeMin
	};
	pitFall3_2[1] = {
		{300,600},
		kPitFallSizeBig
	};
	pitFall3_2[2] = {
		{500,200},
		kPitFallSizeBig
	};

	SafeZone pitFall3_3[kPitFall3_3];
	pitFall3_3[0] = {
		{100,200},
		kPitFallSizeMin
	};
	pitFall3_3[1] = {
		{200,600},
		kPitFallSizeMiddle
	};
	pitFall3_3[2] = {
		{500,200},
		kPitFallSizeBig
	};

	Vector2f reflection = {};

	//プログラムで使うステージの落とし穴の数
	int pitFallNum = kPitFall3_1;

	//プログラムで使う落とし穴
	SafeZone pitFall[5] = {};

	//ゴール
	float goalPositionY = 100.0f;
	bool isGoal = false;

	//敵
	Enemy enemy2_1[kEnemyNumS2_1];
	enemy2_1[0] = {
		{300, 400},
		kEnemySize,
		3,
		true
	};

	float theta;

	for (int i = 0; i < 8; i++) {
		theta = 2.0f / 8.0f * i * 3.14f;
		enemy2_1[0].linePosition[i].x = enemy2_1[0].size / 2 * cosf(theta);
		enemy2_1[0].linePosition[i].x += enemy2_1[0].position.x + enemy2_1[0].size / 2;
		enemy2_1[0].linePosition[i].y = enemy2_1[0].size / 2 * sinf(theta);
		enemy2_1[0].linePosition[i].y += enemy2_1[0].position.y + enemy2_1[0].size / 2;
	}


	//プログラムで使うステージの落とし穴の数
	int enemyNum = kEnemyNumS2_1;

	//プログラムで使う敵
	Enemy enemy[5] = {};


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
		
		switch (scene) {
			case TITLE:
				break;
			case STAGE_SELECT:
				break;
			case PLAY:

				//浮島
				if (stage == S1_1 || stage == S1_2 || stage == S1_3) {
					for (int i = 0; i < safeZoneNum; i++) {
						//プレイヤーが浮島に乗っているか
						if (player.isMove == false && Collision(player, safeZone[i]) == true) {
							player.isCollision = true;
						}
					}
					if (player.isMove == false && player.isCollision == false) {
						player.isAlive = false;
					}
					player.isCollision = false;
					//ゴールまで行ったか
					if (player.position.y <= goalPositionY) {
						isGoal = true;
					}
				}

				//敵
				else if (stage == S2_1 || stage == S2_2 || stage == S2_3) {
					for (int i = 0; i < enemyNum; i++) {

						//プレイヤーが敵にあったか
						reflection = Collision(player, enemy2_1[i]);

						if (reflection.x != 0) {
							player.speed.x = reflection.x * 4;
							player.speed.y = reflection.y * 4;
							player.acceleration.x = float(cos(thetaCount * M_PI)) * -1.0f;
							player.acceleration.y = float(sin(thetaCount * M_PI)) * -1.0f;
						}

						//残機があるか
						if (enemy[i].remain < 0) {
							enemy[i].isAlive = false;
						}
					}
				}

				//落とし穴
				else if (stage == S3_1 || stage == S3_2 || stage == S3_3) {
					for (int i = 0; i < pitFallNum; i++) {
						//プレイヤーが落とし穴にあたったか
						if (player.isMove == false && Collision(player, safeZone[i]) == true) {
							player.isCollision = true;
						}
					}
					if (player.isMove == false && player.isCollision == true) {
						player.isAlive = false;
					}
					player.isCollision = false;
					//ゴールまで行ったか
					if (player.position.y <= goalPositionY) {
						isGoal = true;
					}
				}

				//プレイヤー
				//強さ決定
				if (isSpeedMater == true) {
					speedCount += speedCountAdd;
					if (speedCount <= 0.5f || speedCount >= 5.0f) {
						speedCountAdd *= -1;
					}
					//スペースキーを押したら強さを決める
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
						player.speed.x *= speedCount;
						player.speed.y *= speedCount;
						isSpeedMater = false;
						player.isMove = true;
					}
				}

				//方向決定
				if (isDirectionMater == true) {
					thetaCount += 0.02f;
					if (thetaCount >= 2) {
						thetaCount = 0.0f;
					}

					aimPosition.x = float(cos(thetaCount * M_PI)) * 100;
					aimPosition.y = float(sin(thetaCount * M_PI)) * 100;
					//スペースキーを押したら方向を決める
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
						player.speed.x = float(cos(thetaCount * M_PI)) * 5.0f;
						player.speed.y = float(sin(thetaCount * M_PI)) * 5.0f;
						player.acceleration.x = float(cos(thetaCount * M_PI)) * -1.0f;
						player.acceleration.y = float(sin(thetaCount * M_PI)) * -1.0f;
						isDirectionMater = false;
						isSpeedMater = true;
					}
				}

				//指定した方向に進む
				if (player.isMove == true) {
					player.position.x += player.speed.x;
					player.position.y += player.speed.y;
					player.speed.x += player.acceleration.x;
					player.speed.y += player.acceleration.y;

					//加速度が小さくなったら動きを止める
					if (player.acceleration.x < 0) {
						if (player.speed.x <= 0.0f) {
							player.speed.x = 0.0f;
							player.speed.y = 0.0f;
							player.isMove = false;
							isDirectionMater = true;
						}
					}
					if (player.acceleration.x > 0) {
						if (player.speed.x >= 0.0f) {
							player.speed.x = 0.0f;
							player.speed.y = 0.0f;
							player.isMove = false;
							isDirectionMater = true;
						}
					}
				}



				break;
			case CLEAR:
				break;
			case OVER:
				break;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		switch (scene) {
			case TITLE:
				break;
			case STAGE_SELECT:
				break;
			case PLAY:
				switch (stage) {
					//浮島
					case S1_1:
						for (int i = 0; i < kSafeZoneNum1_1; i++) {
							Novice::DrawBox(safeZone1_1[i].position.x, safeZone1_1[i].position.y, int(safeZone1_1[i].size), int(safeZone1_1[i].size), 0.0f, GREEN, kFillModeSolid);
						}
					case S1_2:
						for (int i = 0; i < kSafeZoneNum1_2; i++) {
							Novice::DrawSprite(safeZone1_2[i].position.x, safeZone1_2[i].position.y, safeZoneTexture, 1.0f, 1.0f, 0.0f, WHITE);
						}
					case S1_3:
						for (int i = 0; i < kSafeZoneNum1_3; i++) {
							Novice::DrawBox(safeZone1_3[i].position.x, safeZone1_3[i].position.y, int(safeZone1_3[i].size), int(safeZone1_3[i].size), 0.0f, GREEN, kFillModeSolid);
						}
						//敵
					case S2_1:
						for (int i = 0; i < kEnemyNumS2_1; i++) {
							Novice::DrawSprite(int(enemy2_1[i].position.x), int(enemy2_1[i].position.y), enemyTexture[0], 1.0f, 1.0f, 0.0f, WHITE);
							Novice::DrawEllipse(int(enemy2_1[i].position.x + enemy2_1[i].size / 2), int(enemy2_1[i].position.y + enemy2_1[i].size / 2), int(enemy2_1[i].size / 2), int(enemy2_1[i].size / 2) , 0.0f,RED,kFillModeWireFrame);

							for (int j = 0; j < 8; j++) {
								Novice::DrawLine(int(enemy2_1[i].linePosition[j].x), int(enemy2_1[i].linePosition[j].y), int(enemy2_1[i].linePosition[(j + 1) % 8].x), int(enemy2_1[i].linePosition[(j + 1) % 8].y), WHITE);
							}
						}
				}

				if (isDirectionMater == true) {
					Novice::DrawEllipse(int(player.position.x + player.size / 2 + aimPosition.x), int(player.position.y + player.size / 2 + aimPosition.y), 10, 10, 0.0f, RED, kFillModeSolid);
				}


				Novice::ScreenPrintf(0, 0, "speedCount = %lf", speedCount);

				//プレイヤー
				if (player.isAlive == true) {
					if (isGoal == true) {
						Novice::DrawSprite(int(player.position.x), int(player.position.y), playerFrontTexture[0], 1.0f, 1.0f, 0.0f, BLUE);
					}
					else {
						Novice::DrawSprite(int(player.position.x), int(player.position.y), playerFrontTexture[0], 1.0f, 1.0f, 0.0f, WHITE);
						Novice::DrawEllipse(int(player.position.x) + 8 + player.size / 2, int(player.position.y) + 8 + player.size / 2, player.size / 2, player.size / 2, 0.0f, RED, kFillModeWireFrame);
					}
				}

				break;
			case CLEAR:
				break;
			case OVER:
				break;
		}
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
