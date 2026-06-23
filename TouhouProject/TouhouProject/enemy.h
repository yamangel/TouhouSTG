#pragma once
#include "bullet.h"

struct BulletPattern
{
	int patternType;
	int bulletCount;
	float speed;
	float interval;
	float spreadAngle;
	int bulletType;
	int bulletW, bulletH;
};

class enemy {
public:
	enemy(int width, int high, float x, float y,
		float vx, float vy, int type,int move, int hp, BulletPattern pattern, int s) : width(width), high(high), x(x), y(y), vx(vx), vy(vy), type(type), hp(hp), pattern(pattern),movePattern(move), scoreValue(s) {
	}
	int width, high;
	float x, y;
	float vx, vy;
	int type;
	int movePattern;
	int hp;
	BulletPattern pattern;
	int scoreValue;
	int frame = 0;
	float frameTimer = 0.0f;
	float shootTimer = 0;
	float hitRadius = 16.0f;
	bool alive = true;
	int bossDir = 0;
	float phaseBase = 0;
	float rotateAngle = 0;
};


void updateEnemy(std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets, float playerX, float playerY, float dt);
void drawEnemy(const std::vector<enemy>& enemies);
