#pragma once

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

	x = ((player.position.x + 8 + player.size / 2.0f) - (safeZone.position.x + 8 + safeZone.size / 2.0f));
	y = ((player.position.y + 8 + player.size / 2.0f) - (safeZone.position.y + 8 + safeZone.size / 2.0f));

	if ((player.size / 2.0f + safeZone.size / 2.0f) * (player.size / 2.0f + safeZone.size / 2.0f) >= x * x + y * y) {
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
void Assignment(SafeZone &safeZone1, SafeZone &safeZone2) {
	safeZone1.position.x = safeZone2.position.x;
	safeZone1.position.y = safeZone2.position.y;
	safeZone1.size = safeZone2.size;
}

/// <summary>
/// 敵の代入
/// </summary>
/// <param name="enemy1">書き換わる変数</param>
/// <param name="enemy2">代入したい変数</param>
void Assignment(Enemy &enemy1, Enemy &enemy2) {
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


Vector2f Collision(Player player, Enemy enemy) {
	Vector2f contactPoint = {};
	Vector2f norlmalVector = {};
	Vector2f directionVector = {};
	Vector2f result = {};
	
	float x = 0.0f;
	float y = 0.0f;

	x = ((player.position.x + 8 + player.size / 2.0f) - (enemy.position.x + 8 + enemy.size / 2.0f));
	y = ((player.position.y + 8 + player.size / 2.0f) - (enemy.position.y + 8 + enemy.size / 2.0f));

	if ((player.size / 2.0f + enemy.size / 2.0f) * (player.size / 2.0f + enemy.size / 2.0f) >= x * x + y * y) {
		contactPoint.x = player.position.x - enemy.position.x;
		contactPoint.y = player.position.y - enemy.position.y;
		contactPoint = Normalize(contactPoint);
		contactPoint.x = contactPoint.x * (enemy.size / 2);
		contactPoint.y = contactPoint.y * (enemy.size / 2);

		norlmalVector.x = contactPoint.x - enemy.position.x;
		norlmalVector.y = contactPoint.y - enemy.position.y;
		norlmalVector = Normalize(norlmalVector);

		directionVector = Normalize(player.speed);

		result.x = -directionVector.x + 2 * norlmalVector.x * (norlmalVector.x * directionVector.x);
		result.y = -directionVector.y + 2 * norlmalVector.y * (norlmalVector.y * directionVector.y);

		return result;

	}
	result = { 0,0 };
	return result;
}