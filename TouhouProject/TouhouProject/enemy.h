#pragma once
#include "bullet.h"
#include <vector>

struct BulletPattern //弹幕类型
{
	int patternType;//0为单发，1为扇形，2为圆形
	int bulletCount;//每一波弹幕数量
	float speed;//速度
	float interval;//两波之间的间隔
	float spreadAngle;
	int bulletType;//子弹贴图
	int bulletW, bulletH;//贴图尺寸
};

class enemy {
public:
	enemy(int width, int high, float x, float y,
		float vx, float vy, int type, int hp, BulletPattern pattern, int s) : width(width), high(high), x(x), y(y), vx(vx), vy(vy), type(type), hp(hp), pattern(pattern), scoreValue(s) {
	}
	int width, high;//图像大小
	float x, y;//位置
	float vx, vy;//速度
	int type;//敌人类型，决定外观和行为//0为基础敌人，1为特殊敌人
	int hp;
	BulletPattern pattern;//射击方式
	int scoreValue;//得分
	int frame = 0;//动画帧
	float frameTimer = 0.0f;//动画帧
	float shootTimer = 0;// 射击冷却计时
	float hitRadius = 16.0f;//碰撞箱半径
	bool alive = true;
};


void updateEnemy(std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets, float playerX, float playerY, float dt);
void drawEnemy(const std::vector<enemy>& enemies);