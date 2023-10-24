#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include <Function.h>
#include <string.h>

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

//ウィンドウサイズ
const int kWindowWideth = 600;
const int kWindowHeight = 720;

//壁の厚さ
const int kWallSize = 32;

//敵の数とサイズ
const int kEnemyNumS2_1 = 1;
const int kEnemyNumS2_2 = 2;
const int kEnemySize = 64;

//敵の子分の数とサイズ
const int kEnemyJrNumS2_1 = 2;
const int kEnemyJrNumS2_2 = 2;
const int kEnemyJrNumS2_3 = 3;
const int kEnemyJrSize = 48;

//浮島の数
const int kSafeZoneNum1_1 = 2;
const int kSafeZoneNum1_2 = 2;
const int kSafeZoneNum1_3 = 3;

//浮島の大きさ
const int kSafeZoneSizeMin = 48;
const int kSafeZoneSizeMiddle = 64;
const int kSafeZoneSizeBig = 96;
const int kSafeZoneSizeT = 128;

//落とし穴の数
const int kPitFall3_1 = 2;
const int kPitFall3_2 = 3;
const int kPitFall3_3 = 3;

//落とし穴の大きさ
const int kPitFallSizeMin = 48;
const int kPitFallSizeMiddle = 64;
const int kPitFallSizeBig = 96;

//マップチップ
const int kBlockSize = 60;
const int kBlockHeight = 36;
const int kBlockWideth = 10;

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
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		48,
		true,
		false,
		false,
		3
	};

	//画像
	int playerFrontTexture[5];
	playerFrontTexture[0] = Novice::LoadTexture("./images/daihuku1.png");
	playerFrontTexture[1] = Novice::LoadTexture("./images/daihuku2.png");
	playerFrontTexture[2] = Novice::LoadTexture("./images/daihuku3.png");
	playerFrontTexture[3] = Novice::LoadTexture("./images/daihuku4.png");
	playerFrontTexture[4] = Novice::LoadTexture("./images/daihuku_damage.png");
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

	int playerDethTexture = Novice::LoadTexture("./images/sibuki.png");

	int playerLife[2];
	playerLife[0] = Novice::LoadTexture("./images/HP1.png");
	playerLife[1] = Novice::LoadTexture("./images/HP2.png");

	int meterTexture[5];
	meterTexture[0] = Novice::LoadTexture("./images/meter1.png");
	meterTexture[1] = Novice::LoadTexture("./images/meter2.png");
	meterTexture[2] = Novice::LoadTexture("./images/meter3.png");
	meterTexture[3] = Novice::LoadTexture("./images/meter4.png");
	meterTexture[4] = Novice::LoadTexture("./images/meter5.png");

	int aimTexture = Novice::LoadTexture("./images/aim.png");

	int enemyTexture[5];
	enemyTexture[0] = Novice::LoadTexture("./images/amechan1.png");
	enemyTexture[1] = Novice::LoadTexture("./images/amechan2.png");
	enemyTexture[2] = Novice::LoadTexture("./images/amechan3.png");
	enemyTexture[3] = Novice::LoadTexture("./images/amechan4.png");
	enemyTexture[4] = Novice::LoadTexture("./images/amechan4-export.png");

	int enemyJrTexture[5];
	enemyJrTexture[0] = Novice::LoadTexture("./images/amechan_new1.png");
	enemyJrTexture[1] = Novice::LoadTexture("./images/amechan_new2.png");
	enemyJrTexture[2] = Novice::LoadTexture("./images/amechan_new3.png");
	enemyJrTexture[3] = Novice::LoadTexture("./images/amechan_new4.png");
	enemyJrTexture[4] = Novice::LoadTexture("./images/amechan_new5.png");

	int safeZoneMinTexture = Novice::LoadTexture("./images/ukishima_small.png");
	int safeZoneMiddleTexture = Novice::LoadTexture("./images/ukishima.png");
	int safeZoneBigTexture = Novice::LoadTexture("./images/ukishima_big.png");
	int safeZoneTeraTexture = Novice::LoadTexture("./images/ukishima_T.png");

	int safeZoneGoalTexture = Novice::LoadTexture("./images/ukishima_goal.png");
	int safeZoneGoalTexture2 = Novice::LoadTexture("./images/ukishima_goal2.png");

//	int pitFallTexture = Novice::LoadTexture("./images/ana.png");

	int titleTexture = Novice::LoadTexture("./images/title.png");
	int selectTexture = Novice::LoadTexture("./images/SELECT.png");
	int stageSuimenTexture = Novice::LoadTexture("./images/stage_suimen2.png");
	int stageEnemyTexture = Novice::LoadTexture("./images/stage_enemy.png");
	int stage3Texture[3];
	stage3Texture[0] = Novice::LoadTexture("./images/miti3.png");
	stage3Texture[1] = Novice::LoadTexture("./images/miti4.png");
	stage3Texture[2] = Novice::LoadTexture("./images/miti2.png");

	int NextStageText = Novice::LoadTexture("./images/nextStageText.png");
	int PushSpaceText = Novice::LoadTexture("./images/PushSpaseTexture.png");

	int clearTexture = Novice::LoadTexture("./images/kuria.png");
	int gameOverTexture = Novice::LoadTexture("./images/gameover.png");

	int tutorialTexture[3];
	tutorialTexture[0] = Novice::LoadTexture("./images/kanban1.png");



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
	Scene nextScene = TITLE;

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

	//スクロール
	int scroll = 0;
	int scrollSpeed = 5;
	bool isScroll = false;

	//浮島
	SafeZone safeZone1_1[kSafeZoneNum1_1];
	safeZone1_1[0] = {
		{300, 600},
		kSafeZoneSizeBig
	};
	safeZone1_1[1] = {
		{300, 300},
		kSafeZoneSizeT
	};

	SafeZone safeZone1_2[2];
	safeZone1_2[0] = {
	{300, 600},
	kSafeZoneSizeBig
	};
	safeZone1_2[1] = {
	{150, 300},
	kSafeZoneSizeBig
	};

	SafeZone safeZone1_3[3];
	safeZone1_3[0] = {
	{300, 600},
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
	int safeZoneNum[3] = { kSafeZoneNum1_1,kSafeZoneNum1_2,kSafeZoneNum1_3 };

	//プログラムで使う浮島
	SafeZone safeZone[3][5] = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < safeZoneNum[i]; j++) {
			Assignment(safeZone[i][j], safeZone1_1[j]);
			safeZone[i][j].position.y -= kWindowHeight * i;
		}
	}
	//落とし穴
	//SafeZone pitFall3_1[kPitFall3_1];
	//pitFall3_1[0] = {
	//	{100,200},
	//	kPitFallSizeBig
	//};
	//pitFall3_1[1] = {
	//	{300,600},
	//	kPitFallSizeBig
	//};

	//SafeZone pitFall3_2[kPitFall3_2];
	//pitFall3_2[0] = {
	//	{100,200},
	//	kPitFallSizeMin
	//};
	//pitFall3_2[1] = {
	//	{300,600},
	//	kPitFallSizeBig
	//};
	//pitFall3_2[2] = {
	//	{500,200},
	//	kPitFallSizeBig
	//};

	//SafeZone pitFall3_3[kPitFall3_3];
	//pitFall3_3[0] = {
	//	{100,200},
	//	kPitFallSizeMin
	//};
	//pitFall3_3[1] = {
	//	{200,600},
	//	kPitFallSizeMiddle
	//};
	//pitFall3_3[2] = {
	//	{500,200},
	//	kPitFallSizeBig
	//};

	Vector2f reflection = {};

	//カットイン
	Vector2 cutInPosition = { 800, 360 };
	Vector2 cutInRadius = { 200, 32 };
	int cutInSpeed = 8;
	bool isCutIn = false;
	int cutInTimer = 0;

	////プログラムで使うステージの落とし穴の数
	//int pitFallNum = kPitFall3_1;

	////プログラムで使う落とし穴
	//SafeZone pitFall[5] = {};

	//ゴール
	float goalPositionY = 100.0f;
	bool isGoal = false;
	bool isGoalAnimation = false;

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

	//敵を時間経過で出すときのタイマー
	int enemyJrAnimationTimer = 0;
	int enemyJrFlameCount = 0;

	float theta = 0.0f;
	Vector2f provisionalPosition = {};

	//プログラムで使うステージの落とし穴の数
	//int enemyNum = kEnemyNumS2_1;

	//プログラムで使う敵
	Enemy enemy = {};

	//プログラムで使う子分
	Enemy enemyJr[3] = {};

	int enemyJrNum = kEnemyJrNumS2_1;

	Enemy enemyJr2_1[kEnemyJrNumS2_1];

	enemyJr2_1[0] = {
		{200, 100},
		kEnemyJrSize,
		0,
		true
	};

	enemyJr2_1[1] = {
		{500, 300},
		kEnemyJrSize,
		0,
		true
	};

	Enemy enemyJr2_2[kEnemyJrNumS2_2];
	enemyJr2_2[0] = {
	{300, 100},
	kEnemyJrSize,
	0,
	true
	};

	enemyJr2_2[1] = {
		{500, 500},
		kEnemyJrSize,
		0,
		true
	};

	Enemy enemyJr2_3[kEnemyJrNumS2_3];

	enemyJr2_3[0] = {
		{300, 100},
		kEnemyJrSize,
		0,
		true
	};

	enemyJr2_3[1] = {
		{500, 500},
		kEnemyJrSize,
		0,
		true
	};

	enemyJr2_3[2] = {
		{350, 500},
		kEnemyJrSize,
		0,
		true
	};


	//プレイヤーのアニメーション
	enum Direction {
		FRONT,
		BACK,
		RIGHT,
		LEFT,
	};

	int playerAnimetionTimer = 0;

	int playerDamageAnimationCount = 0;
	bool isPlayerDamage = false;

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

	int enemyDamageAnimationCount = 0;
	bool isEnemyDamage = false;

	//メーター
	int meterPositionX = 100;
	int meterPositionY = 400;

	//ゲームオーバー
	//int gameOverCount = 0;
	//bool isGameOver = false;
	
	int map[kBlockHeight][kBlockWideth] = {
{1,1,1,1,0,0,1,1,1,1},
{1,1,1,1,0,0,1,1,1,1},
{1,1,1,1,0,0,1,1,1,1},
{1,1,1,0,0,0,0,1,1,1},
{1,1,0,0,1,1,0,0,1,1},
{0,0,0,1,1,1,1,0,0,0},
{0,1,1,1,1,1,1,1,1,0},
{0,0,1,1,1,1,1,1,0,0},
{1,0,0,1,1,1,1,0,0,1},
{1,1,0,0,1,1,0,0,1,1},
{1,1,1,0,0,0,0,1,1,1},
{1,1,1,1,0,0,1,1,1,1},
{1,1,1,1,0,0,1,1,1,1},
{1,1,1,0,0,0,1,1,1,1},
{1,1,0,0,0,1,1,1,1,1},
{1,0,0,0,1,1,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1},
{1,0,0,0,1,1,1,1,1,1},
{1,1,0,0,0,1,1,1,1,1},
{1,1,1,0,0,0,1,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},
{1,1,1,1,0,0,0,1,1,1},

};

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
					playHandle1 = Novice::PlayAudio(audioHandle1, false, 0.5f);
				}
				//Sで次のシーンに行く
				if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
					isNextScene = true;
					nextScene = PLAY;
				}

				//初期化
				scroll = 0;
				PlayerInitialization(player);

				//次のシーンに行くか
				if (isNextScene == true) {
					//BGM停止
					Novice::StopAudio(playHandle1);
					scene = nextScene;
					isNextScene = false;
				}

				break;
//			case STAGE_SELECT:
//#ifdef _DEBUG
//				//Sで次のシーンに行く
//				if (keys[DIK_S] && preKeys[DIK_S] == 0) {
//					isNextScene = true;
//				}
//#endif // _DEBUG


				////次のシーンに行くか
				//if (isNextScene == true) {
				//	//BGM停止
				//	Novice::StopAudio(playHandle1);
				//	scene = PLAY;
				//	isNextScene = false;
				//}

				break;
			case PLAY:

				

				//BGM再生
				if (!Novice::IsPlayingAudio(playHandle2)) {
					playHandle2 = Novice::PlayAudio(audioHandle2, false, 0.5f);
				}

				//浮島
				if (stage == S1_1 || stage == S1_2 || stage == S1_3) {
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < safeZoneNum[i]; j++) {
							//プレイヤーが浮島に乗っているか
							if (player.isMove == false && Collision(player, safeZone[i][j]) == true) {
								player.isCollision = true;
							}
							else if ((stage == S1_2 || stage == S1_3) && player.position.y + scroll > 620) {
								player.isAlive = true;
								player.isCollision = true;
							}
						}
					}
					//ゴールまで行ったか
					if (player.position.y + scroll <= goalPositionY && player.isMove == false && isGoal == false && isCutIn == false) {
						isGoal = true;
						isGoalAnimation = true;
					}

					if (player.isMove == false && player.isCollision == false && isGoal == false && isCutIn == false) {
						player.isAlive = false;
					}
					player.isCollision = false;

					//死んだとき
					if (player.isAlive == false) {
						
					}

					//ゴールした後のアニメーション
					if (player.isMove == true && player.position.y + scroll < 50) {
						player.position.y = 50.0f - float(scroll);
					}

					if (isGoal == true && isGoalAnimation == false) {
						player.position.y -= 4;

						if (player.position.y + scroll + player.radius <= 0 && isScroll == false) {
							isCutIn = true;
							isGoal = false;
						}
					}

					if (isScroll == true) {
						scroll += scrollSpeed;
						if (stage == S1_1 && scroll >= kWindowHeight) {
							scroll = kWindowHeight;
							isNextStage = true;
							isScroll = false;
						}
						if (stage == S1_2 && scroll >= kWindowHeight * 2) {
							scroll = kWindowHeight * 2;
							isNextStage = true;
							isScroll = false;
						}
					}
				}

				//敵
				else if (stage == S2_1 || stage == S2_2 || stage == S2_3) {


					//プレイヤーが敵にあたったか
					provisionalPosition = PushBack(player, enemy);
					if (provisionalPosition.x != 0) {
						player.position.x = provisionalPosition.x;

						theta = ReflectionVector(player, enemy, 0.25f);
						player.position.y = provisionalPosition.y;
						player.speed.x = cosf(theta * float(M_PI)) * 30;
						player.speed.y = sinf(theta * float(M_PI)) * 30;
						player.acceleration.x = -cosf(theta * float(M_PI)) * 2;
						player.acceleration.y = -sinf(theta * float(M_PI)) * 2;
						if (isEnemyDamage == false) {
							enemy.remain--;
						isEnemyDamage = true;
						}
					}
					for (int j = 0; j < enemyJrNum; j++) {
							provisionalPosition = PushBack(player, enemyJr[j]);
							if (provisionalPosition.x != 0) {
								player.position.x = provisionalPosition.x;

								theta = ReflectionVector(player, enemyJr[j], 0.25f);
								player.position.y = provisionalPosition.y;
								player.speed.x = cosf(theta * float(M_PI)) * 30;
								player.speed.y = sinf(theta * float(M_PI)) * 30;
								player.acceleration.x = -cosf(theta * float(M_PI));
								player.acceleration.y = -sinf(theta * float(M_PI));
								if (isPlayerDamage == false) {
									player.remain--;
									isPlayerDamage = true;
								}
							}
					}

					if (isEnemyDamage == true) {
						enemyDamageAnimationCount++;
						if (enemyDamageAnimationCount > 60) {
							isEnemyDamage = false;
							enemyDamageAnimationCount = 0;
						}
					}

					if (enemy.remain <= 0 && enemyDamageAnimationCount >= 50 && isGoal == false) {
						isGoal = true;
						isCutIn = true;
					}

					if (isPlayerDamage == true) {
						playerDamageAnimationCount++;
						if (playerDamageAnimationCount > 60) {
							isPlayerDamage = false;
							playerDamageAnimationCount = 0;
						}
					}

					//残機があるか
					if (enemy.remain <= 0) {
						enemy.isAlive = false;
					}
				}

				//落とし穴
				else if (stage == S3_1 || stage == S3_2 || stage == S3_3) {
					player.topMapPosition.x = int(player.position.x) / kBlockSize;
					player.topMapPosition.y = int(player.position.y - player.radius) / kBlockSize;
					player.bottomMapPosition.x = int(player.position.x) / kBlockSize;
					player.bottomMapPosition.y = int(player.position.y + player.radius) / kBlockSize;
					player.leftMapPosition.x = int(player.position.x - player.radius) / kBlockSize;
					player.leftMapPosition.y = int(player.position.y) / kBlockSize;
					player.rightMapPosition.x = int(player.position.x + player.radius) / kBlockSize;
					player.rightMapPosition.y = int(player.position.y) / kBlockSize;

					//プレイヤーが落とし穴にあたったか
					if (player.isMove == false && map[player.topMapPosition.y][player.topMapPosition.x] == 1) {
						player.isAlive = false;
					}
					//ゴールまで行ったか
					if (player.position.y - scroll <= goalPositionY && player.isMove == false && isGoal == false && isCutIn == false) {
						isGoal = true;
						isGoalAnimation = true;
					}

					if (isGoal == true && isGoalAnimation == false) {
						player.position.y -= 4;

						if (player.position.y - scroll + player.radius <= 0 && isScroll == false) {
							isCutIn = true;
							isGoal = false;
						}
					}

					if (player.isMove == true && player.position.y - scroll < 50) {
						player.position.y = 50.0f + float(scroll);
					}

					if (isScroll == true) {
						scroll -= scrollSpeed;
						if (stage == S3_1 && scroll <= kWindowHeight) {
							scroll = kWindowHeight;
							isNextStage = true;
							isScroll = false;
						}
						if (stage == S3_2 && scroll <= 0) {
							scroll = 0;
							isNextStage = true;
							isScroll = false;
						}
					}

				}

				//プレイヤー
				//強さ決定
				if (isSpeedMeter == true) {
					speedCount += speedCountAdd;
					if (speedCount <= 0.5f || speedCount >= 4.9f) {
						speedCountAdd *= -1;
					}
					//スペースキーを押したら強さを決める
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
						player.speed.x *= speedCount;
						player.speed.y *= speedCount;
						if (stage == S2_1 || stage == S2_2 || stage == S2_3) {
							player.speed.x *= 2;
							player.speed.y *= 2;
						}
						isSpeedMeter = false;
						player.isMove = true;
					}
				}

				//方向決定
				if (isDirectionMater == true && isGoal == false && isCutIn == false) {
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
				if (isGoal == false) {

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
				}

				if (isGoalAnimation == true) {
					playerAnimetionTimer++;

					if (playerAnimetionTimer >= 80) {
						playerCurrentTexture = playerFrontTexture[0];
					}
					else if (playerAnimetionTimer >= 70) {
						playerCurrentTexture = playerFrontTexture[3];
					}
					else if (playerAnimetionTimer >= 60) {
						playerCurrentTexture = playerFrontTexture[2];
					}
					else if (playerAnimetionTimer >= 50) {
						playerCurrentTexture = playerFrontTexture[1];
					}
					else if (playerAnimetionTimer >= 40) {
						playerCurrentTexture = playerFrontTexture[0];
					}
					else if (playerAnimetionTimer >= 30) {
						playerCurrentTexture = playerFrontTexture[3];
					}
					else if (playerAnimetionTimer >= 20) {
						playerCurrentTexture = playerFrontTexture[2];
					}
					else if (playerAnimetionTimer >= 10) {
						playerCurrentTexture = playerFrontTexture[1];
					}
					else if (playerAnimetionTimer >= 0) {
						playerCurrentTexture = playerFrontTexture[0];
					}

					if (playerAnimetionTimer >= 160) {
						playerAnimetionTimer = 0;
						isGoalAnimation = false;
						playerCurrentTexture = playerBackTexture[0];
					}
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
				if (player.isMove == true && isGoal == false) {
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
				if (enemyFlameCount >= 40) {
					enemyAnimeCount = 0;
				}
				else if (enemyFlameCount >= 30) {
					enemyAnimeCount = 1;
				}
				else if (enemyFlameCount >= 20) {
					enemyAnimeCount = 2;
				}
				else if (enemyFlameCount >= 10) {
					enemyAnimeCount = 1;
				}
				else if (enemyFlameCount >= 0) {
					enemyAnimeCount = 0;
				}

				if (enemyFlameCount >= 160) {
					enemyFlameCount = 0;
				}

				enemyJrAnimationTimer++;

				if (enemyJrAnimationTimer >= 40) {
					enemyJrFlameCount = 0;
				}
				else if (enemyJrAnimationTimer >= 35) {
					enemyJrFlameCount = 1;
				}
				else if (enemyJrAnimationTimer >= 30) {
					enemyJrFlameCount = 2;
				}
				else if (enemyJrAnimationTimer >= 25) {
					enemyJrFlameCount = 3;
				}
				else if (enemyJrAnimationTimer >= 20) {
					enemyJrFlameCount = 4;
				}
				else if (enemyJrAnimationTimer >= 15) {
					enemyJrFlameCount = 3;
				}
				else if (enemyJrAnimationTimer >= 10) {
					enemyJrFlameCount = 2;
				}
				else if (enemyJrAnimationTimer >= 5) {
					enemyJrFlameCount = 1;
				}
				else if (enemyJrAnimationTimer >= 0) {
					enemyJrFlameCount = 0;
				}

				if (enemyJrAnimationTimer >= 140) {
					enemyJrAnimationTimer = 0;
				}



#ifdef _DEBUG
				if (keys[DIK_A] && preKeys[DIK_A] == 0) {
					isNextStage = true;
				}
#endif // _DEBUG

				//画面外に行かないための処理
				if (stage == S2_1 || stage == S2_2 || stage == S2_3) {
					if (player.position.y + player.radius >= kWindowHeight - kWallSize) {
						player.position.y = float(kWindowHeight - player.radius - kWallSize);
						player.speed.y *= -1;
						player.acceleration.y *= -1;
					}
					if (player.position.y - player.radius <= 0 + kWallSize) {
						player.position.y = float(player.radius + kWallSize);
						player.speed.y *= -1;
						player.acceleration.y *= -1;
					}
					if (player.position.x + player.radius >= kWindowWideth - kWallSize) {
						player.position.x = float(kWindowWideth - player.radius - kWallSize);
						player.speed.x *= -1;
						player.acceleration.x *= -1;
					}
					if (player.position.x - player.radius <= 0 + kWallSize) {
						player.position.x = float(player.radius + kWallSize);
						player.speed.x *= -1;
						player.acceleration.x *= -1;
					}
				}

				//カットイン
				if (isCutIn == true && (cutInTimer == 0 || cutInTimer >= 60)) {
					cutInPosition.x -= cutInSpeed;

					if (cutInPosition.x <= -cutInRadius.x) {
						if (stage != S1_1 && stage != S1_2 && stage != S3_1 && stage != S3_2) {
						isNextStage = true;
						}
						else {
						isScroll = true;
						}
						cutInPosition.x = kWindowWideth + cutInRadius.x;
						cutInTimer = 0;
						isCutIn = false;
					}
				}
				if (cutInPosition.x <= kWindowWideth / 2) {
					cutInTimer++;
				}

				//死んだとき
				if (player.isAlive == false) {
					isNextScene = true;
					nextScene = OVER;
				}


				//次のステージに行くか
				if (isNextStage == true) {
					//初期化と次のステージ情報
					if (stage != S1_1 && stage != S1_2 && stage != S3_1 && stage != S3_2) {
						PlayerInitialization(player);
					}
					isNextStage = false;
					isGoal = false;
					isGoalAnimation = false;

					switch (stage) {
						case S1_1:
							stage = S1_2;
							break;

						case S1_2:
							stage = S1_3;
							break;

						case S1_3:
							stage = S2_1;
							Assignment(enemy, enemy2_1);
							for (int i = 0; i < enemyJrNum; i++) {
								Assignment(enemyJr[i], enemyJr2_1[i]);
							}
							scroll = 0;
							break;

						case S2_1:
							stage = S2_2;
							Assignment(enemy, enemy2_2);
							enemyJrNum = kEnemyJrNumS2_2;
							for (int i = 0; i < enemyJrNum; i++) {
								Assignment(enemyJr[i], enemyJr2_2[i]);
							}
							break;

						case S2_2:
							stage = S2_3;
							Assignment(enemy, enemy2_3);
							enemyJrNum = kEnemyJrNumS2_3;
							for (int i = 0; i < enemyJrNum; i++) {
								Assignment(enemyJr[i], enemyJr2_3[i]);
							}
							break;

						case S2_3:
							stage = S3_1;
							scroll = kWindowHeight * 2;
							player.position.y += kWindowHeight * 2;
							break;

						case S3_1:
							stage = S3_2;
							break;

						case S3_2:
							stage = S3_3;
							break;
						case S3_3:
							isNextScene = true;
							nextScene = CLEAR;
							scroll = 0;
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
					scene = nextScene;

					//BGM停止
					Novice::StopAudio(playHandle2);
					isNextScene = false;
				}

				break;
			case CLEAR:
				//Sで次のシーンに行く
				if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
					isNextScene = true;
				}

				if (isPlay == true) {
					//BGM再生
					if (!Novice::IsPlayingAudio(playHandle3)) {
						playHandle3 = Novice::PlayAudio(audioHandle3, false, 0.5f);
					}
					isPlay = false;
				}


				//次のシーンに行くか
				if (isNextScene == true) {
					//BGM停止
					Novice::StopAudio(playHandle3);
					scene = TITLE;
					stage = S1_1;
					isNextScene = false;
				}
				break;
			case OVER:
				if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
					isNextScene = true;
				}

				if (isPlay == true) {
					//BGM再生
					if (!Novice::IsPlayingAudio(playHandle3)) {
						playHandle3 = Novice::PlayAudio(audioHandle3, false, 0.5f);
					}
					isPlay = false;
				}


				//次のシーンに行くか
				if (isNextScene == true) {
					//BGM停止
					Novice::StopAudio(playHandle3);
					scene = TITLE;
					stage = S1_1;
					isNextScene = false;
				}

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

					//背景
					Novice::DrawSprite(0, 0, stageSuimenTexture, 1.0f, 1.0f, 0.0f, WHITE);
					
					//ゴールの浮島
					for (int i = 0; i < 3; i++) {
						Novice::DrawSprite(0, -kWindowHeight * i + scroll, safeZoneGoalTexture2, 1.0f, 1.0f, 0.0f, WHITE);
						Novice::DrawSprite(0, -kWindowHeight * i - 100 + scroll, safeZoneGoalTexture, 1.0f, 1.0f, 0.0f, WHITE);
					}

					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < safeZoneNum[i]; j++) {
							if (safeZone[i][j].size == kSafeZoneSizeMin) {
								Novice::DrawSprite(safeZone[i][j].position.x, safeZone[i][j].position.y - kSafeZoneSizeMin / 2 + scroll, safeZoneMinTexture, 1.0f, 1.0f, 0.0f, WHITE);
							}
							else if (safeZone[i][j].size == kSafeZoneSizeMiddle) {
								Novice::DrawSprite(safeZone[i][j].position.x - kSafeZoneSizeMiddle / 2, safeZone[i][j].position.y - kSafeZoneSizeMiddle / 2 + scroll, safeZoneMiddleTexture, 1.0f, 1.0f, 0.0f, WHITE);
							}
							else if (safeZone[i][j].size == kSafeZoneSizeBig) {
								Novice::DrawSprite(safeZone[i][j].position.x - kSafeZoneSizeBig / 2, safeZone[i][j].position.y - kSafeZoneSizeBig / 2 + scroll, safeZoneBigTexture, 1.0f, 1.0f, 0.0f, WHITE);
							}
							else if (safeZone[i][j].size == kSafeZoneSizeT) {
								Novice::DrawSprite(safeZone[i][j].position.x - kSafeZoneSizeT / 2, safeZone[i][j].position.y - kSafeZoneSizeT / 2 + scroll, safeZoneTeraTexture, 1.0f, 1.0f, 0.0f, WHITE);
							}
						}
					}
				}

				//敵
				if (stage == S2_1 || stage == S2_2 || stage == S2_3) {
					Novice::DrawSprite(0, 0, stageEnemyTexture, 1.0f, 1.0f, 0.0f, WHITE);

					if(isEnemyDamage == true && enemyDamageAnimationCount % 2 == 0){
						Novice::DrawSprite(int(enemy.position.x - enemy.radius), int(enemy.position.y - enemy.radius), enemyTexture[3], 1.0f, 1.0f, 0.0f, WHITE);
					}
					else if (enemy.isAlive == true && isEnemyDamage == false) {
						Novice::DrawSprite(int(enemy.position.x - enemy.radius), int(enemy.position.y - enemy.radius), enemyTexture[enemyAnimeCount], 1.0f, 1.0f, 0.0f, WHITE);
					}

					///子分
					for (int i = 0; i < enemyJrNum; i++) {
						Novice::DrawSprite(int(enemyJr[i].position.x - enemyJr[i].size / 2), int(enemyJr[i].position.y - enemyJr[i].size / 2), enemyJrTexture[enemyJrFlameCount], 1.0f, 1.0f, 0.0f, WHITE);
					}

#ifdef _DEBUG
					Novice::DrawEllipse(int(enemy.position.x), int(enemy.position.y), int(enemy.size / 2), int(enemy.size / 2), 0.0f, RED, kFillModeWireFrame);

#endif
				}
				//落とし穴
				if (stage == S3_1 || stage == S3_2 || stage == S3_3) {
					for (int i = 0; i < 3; i++) {
						Novice::DrawSprite(0, kWindowHeight * i - scroll, stage3Texture[i], 1.0f, 1.0f, 0.0f, WHITE);
					}
					for(int i = 0;i < kBlockHeight;i++){
						for (int j = 0; j < kBlockWideth; j++) {
							if (map[i][j] == 1)
								Novice::DrawBox(kBlockSize * j, kBlockSize * i - scroll, kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeSolid);
						}

					}
				}

				//標準
				if (isDirectionMater == true) {
					if (stage == S3_1 || stage == S3_2 || stage == S3_3) {
						Novice::DrawSprite(int(player.position.x + aimPosition.x - 16), int(player.position.y + aimPosition.y - 16 - scroll), aimTexture, 2.0f, 2.0f, 0.0f, WHITE);
					}
					else {
						Novice::DrawSprite(int(player.position.x + aimPosition.x - 16), int(player.position.y + aimPosition.y - 16 + scroll), aimTexture, 2.0f, 2.0f, 0.0f, WHITE);
					}
				}

#ifdef _DEBUG
				Novice::ScreenPrintf(0, 0, "speedCount = %lf", speedCount);
				Novice::ScreenPrintf(0, 60, "speedCount = %f", player.speed.x);
				Novice::ScreenPrintf(0, 80, "speedCount = %f", player.speed.y);
#endif // _DEBUG

				//プレイヤー
				if (player.isAlive == true || isGoal == true) {
					if (stage == S3_1 || stage == S3_2 || stage == S3_3) {
						Novice::DrawSprite(int(player.position.x - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET), int(player.position.y - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET) - scroll, playerCurrentTexture, 1.0f, 1.0f, 0.0f, WHITE);
					}
					else {
						if (isPlayerDamage == true && playerDamageAnimationCount % 2 == 0) {
							Novice::DrawSprite(int(player.position.x - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET), int(player.position.y - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET) + scroll, playerFrontTexture[4], 1.0f, 1.0f, 0.0f, WHITE);
						}
						else if(isPlayerDamage == false){
						Novice::DrawSprite(int(player.position.x - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET), int(player.position.y - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET) + scroll, playerCurrentTexture, 1.0f, 1.0f, 0.0f, WHITE);
						}
					}
				}
				else {
					Novice::DrawSprite(int(player.position.x - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET), int(player.position.y - (player.size) / 2.0f - PLAYER_PIXCEL_OFFSET) + scroll, playerDethTexture, 1.0f, 1.0f, 0.0f, WHITE);
				}

				//\看板
				Novice::DrawSprite(300, 0, tutorialTexture[0], 1.0f, 1.0f, 0.0f, WHITE);

				//HP
				if (stage == S2_1 || stage == S2_2 || stage == S2_3) {
					for (int i = 0; i < 3; i++) {
						if (player.remain > i) {
							Novice::DrawSprite(i * 40 + 30, 50, playerLife[0], 1.0f, 1.0f, 0.0f, WHITE);
						}
						else {
							Novice::DrawSprite(i * 40 + 30, 50, playerLife[1], 1.0f, 1.0f, 0.0f, WHITE);
						}
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

				//pushSpace
				Novice::DrawSprite(360, 650, PushSpaceText, 1.0f, 1.0f, 0.0f, WHITE);

				//カットイン
				if (isCutIn == true) {
					Novice::DrawSprite(cutInPosition.x - cutInRadius.x, cutInPosition.y - cutInRadius.y, NextStageText, 1.0f, 1.0f, 0.0f, WHITE);
				}

				break;
			case CLEAR:
				Novice::DrawSprite(0, 0, clearTexture, 1.0f, 1.0f, 0.0f, WHITE);
				break;
			case OVER:
				Novice::DrawSprite(0, 0, gameOverTexture, 1.0f, 1.0f, 0.0f, WHITE);
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
