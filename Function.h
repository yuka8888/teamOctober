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
	bool isAlive;
	int remain;
};


