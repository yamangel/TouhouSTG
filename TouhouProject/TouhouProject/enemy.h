#pragma once
#include "Bullet.h"
#include <vector>

struct BulletPattern //弹幕类型
{
	int patternType;//0为单发，1为圆形，2为扇形
	int bulletCount;//每一波弹幕数量
	float speed;//速度
	float interval;//两波之间的间隔
	float spreadAngle;
	int bulletType;//子弹贴图
	int bulletW, bulletH;//贴图尺寸
};

class enemy{
public:
	enemy(int width, int high, float x, float y, 
		float vx, float vy, int type, int hp, BulletPattern pattern) : width(width), high(high), x(x), y(y), vx(vx), vy(vy), type(type), hp(hp), pattern(pattern) {}
	int width, high;
	float x, y;
	float vx, vy;
	int frame = 0;
	float frameTimer = 0.0f;
	int type;//敌人类型，决定外观和行为//0为基础敌人，1为特殊敌人
	int hp;
	float shootTimer = 0;// 射击冷却计时
	BulletPattern pattern;
	float hitRadius = 16.0f;
	bool alive = true;
};


void updateEnemy(std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets,float playerX, float playerY, float dt);
void drawEnemy(const std::vector<enemy>& enemies);