#pragma once
#include "bullet.h"
#include <vector>
class player
{
public:
	player(int width, int high, float x,float y,float speed, float slowspeed,int hp) : width(width), high(high), x(x), y(y),speed(speed), slowspeed(slowspeed), hp(hp) {}
	int width, high;//size
	float x, y;//位置
	float speed;//移动速度
	float slowspeed;//低速移动速度
	int hp;//血量
	int facing = 0;//方向
	int frame = 0;//动画帧
	float frameTimer = 0.0f;//动画帧计时器
	float hitRadius = 6.0f;//碰撞箱半径
	float invincibleTimer = 0;//剩余无敌时间
	float power = 1.0f;//灵力值
	float maxPower = 4.0f;//灵力上限
};
void updatePlayer(player& p, float dt);
void drawPlayer(const player& p);
void drawplayerCollisions(player& player, std::vector<Bullet>& enemyBullets);