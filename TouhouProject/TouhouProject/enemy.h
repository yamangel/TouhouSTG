#pragma once
#include <vector>
class enemy
{
public:
	enemy(int width, int high, float x, float y, 
		float vx, float vy, int type,int hp) : width(width), high(high), x(x), y(y), vx(vx), vy(vy), type(type), hp(hp) {}
	int width, high;
	float x, y;
	float vx, vy;
	int frame = 0;
	float frameTimer = 0.0f;
	int type;//敌人类型，决定外观和行为//0为基础敌人，1为特殊敌人
	int hp;
	float hitRadius = 16.0f;
	bool alive = true;
};

void updateEnemy(std::vector<enemy>& enemies, float dt);
void drawEnemy(const std::vector<enemy>& enemies);