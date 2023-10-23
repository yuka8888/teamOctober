#pragma once
#define PLAYER_PIXCEL_OFFSET 8.0f

struct Vector2 {
	int x;
	int y;
};

struct Vector2f {
	float x;
	float y;
};

struct Player {
	Vector2f position;
	Vector2f speed;
	Vector2f acceleration;
	int size;
	bool isAlive;
	bool isMove;
	bool isCollision;
	int remain;
	int radius = 24;
};


struct SafeZone {
	Vector2 position;
	float size;
};

struct Enemy {
	Vector2f position;
	float size;
	int remain;
	bool isAlive;
	Vector2f linePosition[8];
	int radius = 32;
};


enum Scene {
	TITLE,
	STAGE_SELECT,
	PLAY,
	CLEAR,
	OVER
};

enum Stage {
	S1_1,
	S1_2,
	S1_3,
	S2_1,
	S2_2,
	S2_3,
	S3_1,
	S3_2,
	S3_3,
};

bool Collision(Player player, SafeZone safeZone) {
	float x = 0.0f;
	float y = 0.0f;

	x = player.position.x - safeZone.position.x;
	y = player.position.y - safeZone.position.y;

	if ((player.radius+ safeZone.size / 2.0f) * (player.radius + safeZone.size / 2.0f) >= x * x + y * y) {
		return true;
	}

	return false;

}

/// <summary>
/// 浮島、落とし穴の代入
/// </summary>
/// <param name="safeZone1">書き換わる変数</param>
/// <param name="safeZone2">代入したい変数</param>
/// <returns></returns>
void Assignment(SafeZone& safeZone1, SafeZone& safeZone2) {
	safeZone1.position.x = safeZone2.position.x;
	safeZone1.position.y = safeZone2.position.y;
	safeZone1.size = safeZone2.size;
}

/// <summary>
/// 敵の代入
/// </summary>
/// <param name="enemy1">書き換わる変数</param>
/// <param name="enemy2">代入したい変数</param>
void Assignment(Enemy& enemy1, Enemy& enemy2) {
	enemy1.isAlive = enemy2.isAlive;
	enemy1.position.x = enemy2.position.x;
	enemy1.position.y = enemy2.position.y;
	enemy1.remain = enemy2.remain;
	enemy1.size = enemy2.size;
}

/// <summary>
/// 外積
/// </summary>
/// <param name="obj1"></param>
/// <param name="obj2"></param>
/// <returns></returns>
float CrossProduct(Vector2f const& obj1, Vector2f const& obj2) {
	return obj1.x * obj2.y - obj1.y * obj2.x;
}

/// <summary>
/// 内積
/// </summary>
/// <param name="obj1"></param>
/// <param name="obj2"></param>
/// <returns></returns>
float Dot(Vector2f const& obj1, Vector2f const& obj2) {
	return obj1.x * obj2.x + obj1.y * obj2.y;
}


/// <summary>
/// 最短距離
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
float Length(Vector2f const& obj) {
	return sqrtf(obj.x * obj.x + obj.y * obj.y);
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
Vector2f Normalize(Vector2f const& obj) {
	float length = 0;
	Vector2f newObj = {};

	length = Length(obj);

	newObj.x = obj.x;
	newObj.y = obj.y;

	if (length != 0.0f) {
		newObj.x = obj.x / length;
		newObj.y = obj.y / length;
	}
	return newObj;
}

/// <summary>
/// 敵の押し戻し処理
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
/// <returns></returns>
Vector2f PushBack(Player player, Enemy enemy) {
	//接地点
	Vector2f contactPoint = {};
	//法線ベクトル
	Vector2f norlmalVector = {};
	Vector2f directionVector = {};
	//float result = 0.0f;
	Vector2f reflection = {};

	float x = 0.0f;
	float y = 0.0f;

	x = (player.position.x) - (enemy.position.x);
	y = (player.position.y) - (enemy.position.y);
	Length({ x,y });

	if (Length({ x,y }) <= player.radius + enemy.radius) {

		//当たる前の座標に戻す
		player.position.x -= player.speed.x;
		player.position.y -= player.speed.y;

		directionVector.x = player.position.x - enemy.position.x;
		directionVector.y = player.position.y - enemy.position.y;
		directionVector = Normalize(directionVector);

		contactPoint.x = directionVector.x * (enemy.radius) + enemy.position.x;
		contactPoint.y = directionVector.y * (enemy.radius) + enemy.position.y;

		player.position.x = contactPoint.x + directionVector.x * (player.radius + 1.0f);
		player.position.y = contactPoint.y + directionVector.y * (player.radius + 1.0f);

		//norlmalVector.x = contactPoint.x - enemy.position.x;
		//norlmalVector.y = contactPoint.y - enemy.position.y;
		//norlmalVector = Normalize(norlmalVector);

		//directionVector = Normalize(player.speed);

		//reflection.x = -directionVector.x + 2 * norlmalVector.x * Dot(norlmalVector, directionVector);
		//reflection.y = -directionVector.y + 2 * norlmalVector.y * Dot(norlmalVector, directionVector);

		return player.position;

	}
	reflection = { 0.0f,0.0f };
	return reflection;
}

/// <summary>
/// 敵の反射処理
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
/// <param name="angle"></param>
/// <returns></returns>
float ReflectionVector(Player player, Enemy enemy, float angle) {
	Vector2f directionVector = {};
	Vector2f Oligin = { 1.0f, 0.0f };
	Vector2f provisionalPosition = {};
	float theta = 0.0f;

	directionVector.x = player.position.x - enemy.position.x;
	directionVector.y = player.position.y - enemy.position.y;
	directionVector = Normalize(directionVector);

	if (player.position.y >= enemy.position.y + enemy.size / 2) {
		Oligin = { -1.0f, 0.0f };
	}
	Length(directionVector);
	Length(Oligin);
	theta = Dot(player.speed, Oligin) / (Length(player.speed) * Length(Oligin));

	theta += angle;

	provisionalPosition.x = player.position.x + (cosf(theta * 3.1415f) * (player.size / 2.0f));
	provisionalPosition.y = player.position.y + (sinf(theta * 3.1415f) * (player.size / 2.0f));

	float x = ((provisionalPosition.x + player.size / 2.0f) - (enemy.position.x + enemy.size / 2.0f));
	float y = ((provisionalPosition.y + player.size / 2.0f) - (enemy.position.y + enemy.size / 2.0f));

	if ((player.size / 2.0f + enemy.size / 2.0f) * (player.size / 2.0f + enemy.size / 2.0f) >= x * x + y * y) {
		theta -= angle * 2;

		return theta;
	}

	return theta;

}

float Angle(Vector2f reflection) {
	return (reflection.x * 1.0f + reflection.y * 0.0f) / sqrtf(reflection.x * reflection.x + reflection.y * reflection.y) * sqrtf(1.0f * 1.0f + 0.0f * 0.0f);
}

int ToDegree(float radian) {
	return (int)(radian * 180.0f / M_PI);
}

/// <summary>
/// プレイヤーの初期化
/// </summary>
/// <param name="player"></param>
void PlayerInitialization(Player& player) {
	player.isAlive = true;
	player.position = { 300, 100 };
	player.remain = 3;
}
