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
const int kSafeZoneSizeMin = 48;
const int kSafeZoneSizeMiddle = 64;
const int kSafeZoneSizeBig = 96;

//落とし穴の数
const int kPitFall3_1 = 2;
const int kPitFall3_2 = 3;
const int kPitFall3_3 = 3;

//落とし穴の大きさ
const int kPitFallSizeMin = 48;
const int kPitFallSizeMiddle = 64;
const int kPitFallSizeBig = 96;

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
	int playerRightTexture[4];
	playerRightTexture[0] = Novice::LoadTexture("./images/daihuku_right1.png");
	playerRightTexture[1] = Novice::LoadTexture("./images/daihuku_right2.png");
	playerRightTexture[2] = Novice::LoadTexture("./images/daihuku_right3.png");
	playerRightTexture[3] = Novice::LoadTexture("./images/daihuku_right4.png");
	int playerLeftTexture[4];
	playerLeftTexture[0] = Novice::LoadTexture("./images/daihuku1.png");
	playerLeftTexture[1] = Novice::LoadTexture("./images/daihuku2.png");
	playerLeftTexture[2] = Novice::LoadTexture("./images/daihuku3.png");
	playerLeftTexture[3] = Novice::LoadTexture("./images/daihuku4.png");
	int playerBackTexture[4];
	playerBackTexture[0] = Novice::LoadTexture("./images/daihuku_back1.png");
	playerBackTexture[1] = Novice::LoadTexture("./images/daihuku_back2.png");
	playerBackTexture[2] = Novice::LoadTexture("./images/daihuku_back3.png");
	playerBackTexture[3] = Novice::LoadTexture("./images/daihuku_back4.png");

	int meterTexture[5];
	meterTexture[0] = Novice::LoadTexture("./images/meter1.png");
	meterTexture[1] = Novice::LoadTexture("./images/meter2.png");
	meterTexture[2] = Novice::LoadTexture("./images/meter3.png");
	meterTexture[3] = Novice::LoadTexture("./images/meter4.png");
	meterTexture[4] = Novice::LoadTexture("./images/meter5.png");

	int enemyTexture[4];
	enemyTexture[0] = Novice::LoadTexture("./images/amechan1.png");
	enemyTexture[1] = Novice::LoadTexture("./images/amechan2.png");
	enemyTexture[2] = Novice::LoadTexture("./images/amechan3.png");
	enemyTexture[3] = Novice::LoadTexture("./images/amechan4.png");

	int safeZoneMinTexture = Novice::LoadTexture("./images/ukishima_small.png");
	int safeZoneMiddleTexture = Novice::LoadTexture("./images/ukishima.png");
	int safeZoneBigTexture = Novice::LoadTexture("./images/ukishima_big.png");

	int pitFallTexture = Novice::LoadTexture("./images/ana.png");

	int titleTexture = Novice::LoadTexture("./images/TITLE.png");
	int selectTexture = Novice::LoadTexture("./images/SELECT.png");
	int stageSuimenTexture = Novice::LoadTexture("./images/stage_suimen.png");
	int stageEnemyTexture = Novice::LoadTexture("./images/stage_enemy.png");
	int stageAnaTexture = Novice::LoadTexture("./images/stage_ana.png");

	//BGM
	int audioHandle1 = Novice::LoadAudio("./sounds/title.mp3");
	int audioHandle2 = Novice::LoadAudio("./sounds/stage.mp3");
	int audioHandle3 = Novice::LoadAudio("./sounds/clear.mp3");
	bool isPlay = false;

	//プレイハンドル宣言
	int playHandle1 = -1;
	int playHandle2 = -1;
	int playHandle3 = -1;

	//シーン
	Scene scene = TITLE;

	Stage stage = S1_1;

	bool isNextScene = false;

	bool isNextStage = false;

	//標準
	//float theta = 0.0f;
	float thetaCount = 0.0f;

	Vector2f aimPosition = { 0,0 };

	float speedCount = 0.6f;
	float speedCountAdd = 0.1f;

	bool isDirectionMater = true;
	bool isSpeedMeter = false;

	//浮島
	SafeZone safeZone1_1[kSafeZoneNum1_1];
	safeZone1_1[0] = {
		{300, 600},
		kSafeZoneSizeMiddle
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
	for (int i = 0; i < safeZoneNum; i++) {
		Assignment(safeZone[i], safeZone1_1[i]);
	}

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
	Enemy enemy2_1 = {
		{300, 400},
		kEnemySize,
		3,
		true
	};

	Enemy enemy2_2 = {
		{300, 500},
		kEnemySize,
		3,
		true
	};

	Enemy enemy2_3 = {
		{200, 600},
		kEnemySize,
		3,
		true
	};

	//float theta;
	Vector2f provisionalPosition = {};

	//プログラムで使うステージの落とし穴の数
	int enemyNum = kEnemyNumS2_1;

	//プログラムで使う敵
	Enemy enemy = {};

	//プレイヤーのアニメーション
	enum Direction {
		FRONT,
		BACK,
		RIGHT,
		LEFT,
	};

	//現在の向き
	int playerDirection = Direction::FRONT;
	//表示中の画像
	int playerCurrentTexture = playerFrontTexture[0];
	//int flameCount = 0;
	int playerAnimeCount = 0;
	//アニメーション避難用変数
	float animationX = 0;
	float animationY = 0;

	//敵のアニメーション
	//int enemyCurrentTexture = enemyTexture[0];
	int enemyAnimeCount = 0;
	int enemyFlameCount = 0;

	//メーター
	int meterPositionX = 100;
	int meterPositionY = 400;


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

				//BGM再生
				if (!Novice::IsPlayingAudio(playHandle1)) {
					playHandle1 = Novice::PlayAudio(audioHandle1, false, 1.0f);
				}
#ifdef _DEBUG
				//Sで次のシーンに行く
				if (keys[DIK_S] && preKeys[DIK_S] == 0) {
					isNextScene = true;
				}
#endif // _DEBUG


				//次のシーンに行くか
				if (isNextScene == true) {
					scene = STAGE_SELECT;
					isNextScene = false;
				}

				break;
			case STAGE_SELECT:
#ifdef _DEBUG
				//Sで次のシーンに行く
				if (keys[DIK_S] && preKeys[DIK_S] == 0) {
					isNextScene = true;
				}
#endif // _DEBUG


				//次のシーンに行くか
				if (isNextScene == true) {
					//BGM停止
					Novice::StopAudio(playHandle1);
					scene = PLAY;
					isNextScene = false;
				}

				break;
			case PLAY:

				//BGM再生
				if (!Novice::IsPlayingAudio(playHandle2)) {
					playHandle2 = Novice::PlayAudio(audioHandle2, false, 1.0f);
				}

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
						provisionalPosition = PushBack(player, enemy2_1);

						if (provisionalPosition.x != 0) {
							player.position.x = provisionalPosition.x;

							//thetaCount = ReflectionVector(player, enemy2_1[i], 0.25f);
							player.position.y = provisionalPosition.y;
							//player.speed.x = cosf(theta * float(M_PI)) * 10;
							//player.speed.y = sinf(theta * float(M_PI)) * 10;
							//player.acceleration.x = -cosf(theta * float(M_PI));
							//player.acceleration.y = -sinf(theta * float(M_PI));

							player.speed.x = 0.0f;
							player.speed.y = 0.0f;
							player.acceleration.x = 0.0f;
							player.acceleration.y = 0.0f;
							provisionalPosition = { 0.0f,0.0f };
						}

						//残機があるか
						if (enemy.remain < 0) {
							enemy.isAlive = false;
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
				if (isSpeedMeter == true) {
					speedCount += speedCountAdd;
					if (speedCount <= 0.5f || speedCount >= 5.0f) {
						speedCountAdd *= -1;
					}
					//スペースキーを押したら強さを決める
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
						player.speed.x *= speedCount;
						player.speed.y *= speedCount;
						isSpeedMeter = false;
						player.isMove = true;
					}
				}

				//方向決定
				if (isDirectionMater == true) {
					thetaCount += 0.02f;
					if (thetaCount >= 2) {
						thetaCount = 0.0f;
					}

					aimPosition.x = cosf(thetaCount * float(M_PI)) * 100;
					aimPosition.y = sinf(thetaCount * float(M_PI)) * 100;
					//スペースキーを押したら方向を決める
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
						player.speed.x = cosf(thetaCount * float(M_PI)) * 5.0f;
						player.speed.y = sinf(thetaCount * float(M_PI)) * 5.0f;
						player.acceleration.x = cosf(thetaCount * float(M_PI)) * -1.0f;
						player.acceleration.y = sinf(thetaCount * float(M_PI)) * -1.0f;
						isDirectionMater = false;
						isSpeedMeter = true;
					}
				}

				//アニメーション
				if (player.speed.x == 0 && player.speed.y == 0) {
					playerDirection = Direction::FRONT;
				}

				if (player.speed.x > 0 && player.speed.y > 0) { //270~360
					if (player.speed.x >= player.speed.y) {
						//右向き
						playerDirection = Direction::RIGHT;
					}
					else {
						//下向き
						playerDirection = Direction::FRONT;
					}
				}
				else if (player.speed.x > 0 && player.speed.y < 0) { //0~90
					animationY = player.speed.y;
					animationY *= -1;
					if (player.speed.x >= animationY) {
						//右向き
						playerDirection = Direction::RIGHT;
					}
					else {
						//上向き
						playerDirection = Direction::BACK;
					}
				}
				else if (player.speed.x < 0 && player.speed.y < 0) { //90~180
					if (player.speed.x <= player.speed.y) {
						//左向き
						playerDirection = Direction::LEFT;
					}
					else {
						//下向き
						playerDirection = Direction::BACK;
					}
				}
				else if (player.speed.x < 0 && player.speed.y > 0) { //180~270
					animationX = player.speed.x;
					animationX *= -1;
					if (animationX <= player.speed.y) {
						//左向き
						playerDirection = Direction::LEFT;
					}
					else {
						//下向き
						playerDirection = Direction::FRONT;
					}
				}

				//アニメーション切り替え処理
				switch (playerDirection) {
					case Direction::FRONT:
						playerCurrentTexture = playerFrontTexture[playerAnimeCount];
						break;
					case Direction::BACK:
						playerCurrentTexture = playerBackTexture[playerAnimeCount];
						break;
					case Direction::LEFT:
						playerCurrentTexture = playerLeftTexture[playerAnimeCount];
						break;
					case Direction::RIGHT:
						playerCurrentTexture = playerRightTexture[playerAnimeCount];
						break;
				}

				//アニメーションのループ
				/*flameCount++;
				if (playerAnimeCount % 10 == 0) {
					playerAnimeCount++;
					if (playerAnimeCount > 3) {
						playerAnimeCount = 0;
					}
				}*/

				//指定した方向に進む
				if (player.isMove == true) {
					player.position.x += player.speed.x;
					player.position.y += player.speed.y;
					player.speed.x += player.acceleration.x;
					player.speed.y += player.acceleration.y;



					//加速度が小さくなったら動きを止める
					if (player.acceleration.x <= 0) {
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

				//敵のアニメーション
				enemyFlameCount++;
				if (enemyFlameCount % 50 == 0) {
					enemyAnimeCount++;
					if (enemyAnimeCount > 2) {
						enemyAnimeCount = 0;
					}
				}

#ifdef _DEBUG
				if (keys[DIK_A] && preKeys[DIK_A] == 0) {
					isNextStage = true;
				}
#endif // _DEBUG


				//次のステージに行くか
				if (isNextStage == true) {
					//初期化と次のステージ情報
					PlayerInitialization(player);
					isNextStage = false;
					isGoal = false;

					switch (stage) {
						case S1_1:
							stage = S1_2;
							safeZoneNum = kSafeZoneNum1_2;
							for (int i = 0; i < safeZoneNum; i++) {
								Assignment(safeZone[i], safeZone1_2[i]);
							}
							break;

						case S1_2:
							stage = S1_3;
							safeZoneNum = kSafeZoneNum1_3;
							for (int i = 0; i < safeZoneNum; i++) {
								Assignment(safeZone[i], safeZone1_2[i]);
							}
							break;

						case S1_3:
							stage = S2_1;
							Assignment(enemy, enemy2_1);
							break;

						case S2_1:
							stage = S2_2;
							Assignment(enemy, enemy2_2);
							break;

						case S2_2:
							stage = S2_3;
							Assignment(enemy, enemy2_3);
							break;

						case S2_3:
							stage = S3_1;
							for (int i = 0; i < pitFallNum; i++) {
								Assignment(pitFall[i], pitFall3_1[i]);
							}
							break;

						case S3_1:
							stage = S3_2;
							for (int i = 0; i < pitFallNum; i++) {
								Assignment(pitFall[i], pitFall3_2[i]);
							}
							break;

						case S3_2:
							stage = S3_3;
							for (int i = 0; i < pitFallNum; i++) {
								Assignment(pitFall[i], pitFall3_3[i]);
							}
							break;

					}
				}

#ifdef _DEBUG
				//Sで次のシーンに行く
				if (keys[DIK_S] && preKeys[DIK_S] == 0) {
					isNextScene = true;
				}
#endif // _DEBUG

				//次のシーンに行くか
				if (isNextScene == true) {
					isPlay = true;
					scene = CLEAR;

					//BGM停止
					Novice::StopAudio(playHandle2);
					isNextScene = false;
				}

				break;
			case CLEAR:
#ifdef _DEBUG
				//Sで次のシーンに行く
				if (keys[DIK_S] && preKeys[DIK_S] == 0) {
					isNextScene = true;
				}
#endif // _DEBUG

				if (isPlay == true) {
					//BGM再生
					if (!Novice::IsPlayingAudio(playHandle3)) {
						playHandle3 = Novice::PlayAudio(audioHandle3, false, 1.0f);
					}
					isPlay = false;
				}


				//次のシーンに行くか
				if (isNextScene == true) {
					//BGM停止
					Novice::StopAudio(playHandle3);
					scene = TITLE;
					isNextScene = false;
				}
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

				Novice::DrawSprite(0, 0, titleTexture, 1.0f, 1.0f, 0.0f, WHITE);

				break;
			case STAGE_SELECT:

				Novice::DrawSprite(0, 0, selectTexture, 1.0f, 1.0f, 0.0f, WHITE);

				break;
			case PLAY:
				//浮島
				if (stage == S1_1 || stage == S1_2 || stage == S1_3) {

					Novice::DrawSprite(0, 0, stageSuimenTexture, 1.0f, 1.0f, 0.0f, WHITE);

					for (int i = 0; i < safeZoneNum; i++) {

						if (safeZone[i].size == kSafeZoneSizeMin) {
							Novice::DrawSprite(safeZone[i].position.x - kSafeZoneSizeMin / 2, safeZone[i].position.y - kSafeZoneSizeMin / 2, safeZoneMinTexture, 1.0f, 1.0f, 0.0f, WHITE);
						}
						else if (safeZone[i].size == kSafeZoneSizeMiddle) {
							Novice::DrawSprite(safeZone[i].position.x - kSafeZoneSizeMiddle / 2, safeZone[i].position.y - kSafeZoneSizeMiddle / 2, safeZoneMiddleTexture, 1.0f, 1.0f, 0.0f, WHITE);
						}
						else if (safeZone[i].size == kSafeZoneSizeBig) {
							Novice::DrawSprite(safeZone[i].position.x - kSafeZoneSizeBig / 2, safeZone[i].position.y - kSafeZoneSizeMiddle / 2, safeZoneBigTexture, 1.0f, 1.0f, 0.0f, WHITE);
						}
					}
				}

				//敵
				if (stage == S2_1 || stage == S2_2 || stage == S2_3) {
					Novice::DrawSprite(0, 0, stageEnemyTexture, 1.0f, 1.0f, 0.0f, WHITE);


					Novice::DrawSprite(int(enemy.position.x - enemy.radius), int(enemy.position.y - enemy.radius), enemyTexture[enemyAnimeCount], 1.0f, 1.0f, 0.0f, WHITE);
#ifdef _DEBUG
					Novice::DrawEllipse(int(enemy.position.x), int(enemy.position.y), int(enemy.size / 2), int(enemy.size / 2), 0.0f, RED, kFillModeWireFrame);
				}
#endif

				//落とし穴
				if (stage == S3_1 || stage == S3_2 || stage == S3_3) {

					Novice::DrawSprite(0, 0, stageAnaTexture, 1.0f, 1.0f, 0.0f, WHITE);

					for (int i = 0; i < pitFallNum; i++) {
						if (pitFall[i].size == kPitFallSizeMin) {
							Novice::DrawSprite(pitFall[i].position.x - kPitFallSizeMin / 2, pitFall[i].position.y - kPitFallSizeMin / 2, pitFallTexture, 0.75f, 0.75f, 0.0f, WHITE);
						}
						else if (pitFall[i].size == kPitFallSizeMiddle) {
							Novice::DrawSprite(pitFall[i].position.x - kPitFallSizeMiddle / 2, pitFall[i].position.y - kPitFallSizeMiddle / 2, pitFallTexture, 1.0f, 1.0f, 0.0f, WHITE);
						}
						else if (pitFall[i].size == kPitFallSizeBig) {
							Novice::DrawSprite(pitFall[i].position.x - kPitFallSizeBig / 2, pitFall[i].position.y - kPitFallSizeMiddle / 2, pitFallTexture, 1.5f, 1.5f, 0.0f, WHITE);
						}
					}
				}

				if (isDirectionMater == true) {
					Novice::DrawEllipse(int(player.position.x + player.size / 2 + aimPosition.x), int(player.position.y + player.size / 2 + aimPosition.y), 10, 10, 0.0f, RED, kFillModeSolid);
				}

#ifdef _DEBUG
				Novice::ScreenPrintf(0, 0, "speedCount = %lf", speedCount);
				Novice::ScreenPrintf(0, 60, "speedCount = %f", player.speed.x);
				Novice::ScreenPrintf(0, 80, "speedCount = %f", player.speed.y);
#endif // _DEBUG

				//プレイヤー
				if (player.isAlive == true) {
					if (isGoal == true) {
						Novice::DrawSprite(int(player.position.x - (player.size) / 2.0f), int(player.position.y - (player.size) / 2.0f), playerCurrentTexture, 1.0f, 1.0f, 0.0f, BLUE);
					}
					else {
						Novice::DrawSprite(int(player.position.x - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET), int(player.position.y - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET), playerCurrentTexture, 1.0f, 1.0f, 0.0f, WHITE);
#ifdef _DEBUG
						Novice::DrawLine(int(player.position.x), int(player.position.y), int(player.position.x + reflection.x * 50), int(player.position.y + reflection.y * 50), RED);
						Novice::DrawEllipse(int(player.position.x), int(player.position.y), player.size / 2, player.size / 2, 0.0f, RED, kFillModeWireFrame);

#endif // !_DEBUG
					}

				}

				//メーター
				if (isSpeedMeter == true) {
					if (speedCount > 0 && speedCount < 1) {
						Novice::DrawSprite(meterPositionX, meterPositionY, meterTexture[0], 1.0f, 1.0f, 0.0f, WHITE);
					}
					else if (speedCount >= 1 && speedCount < 2) {
						Novice::DrawSprite(meterPositionX, meterPositionY, meterTexture[1], 1.0f, 1.0f, 0.0f, WHITE);
					}
					else if (speedCount >= 2 && speedCount < 3) {
						Novice::DrawSprite(meterPositionX, meterPositionY, meterTexture[2], 1.0f, 1.0f, 0.0f, WHITE);
					}
					else if (speedCount >= 3 && speedCount < 4) {
						Novice::DrawSprite(meterPositionX, meterPositionY, meterTexture[3], 1.0f, 1.0f, 0.0f, WHITE);
					}
					else if (speedCount >= 4 && speedCount < 5) {
						Novice::DrawSprite(meterPositionX, meterPositionY, meterTexture[4], 1.0f, 1.0f, 0.0f, WHITE);
					}
				}
				break;
			case CLEAR:
				break;
			case OVER:
				break;
		}
#ifdef _DEBUG
		Novice::ScreenPrintf(0, 20, "SCENE = %d", scene);
		Novice::ScreenPrintf(0, 40, "stage = %d", stage);
#endif // _DEBUG

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
