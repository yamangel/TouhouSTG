#pragma once
#include "enemy.h"

struct  SpawnEntry
{
	float time;
	int enemyNum;
	int type;
	int movePattern;
	float x, y;
	float vx, vy;
	float interval;
	int hp;
	float spread;
	BulletPattern pattern;
	int scoreValue;
	SpawnEntry(float time, int enemyNum, int type, int movePattern, 
		float x, float y, float vx, float vy, float interval, int hp, float spread,BulletPattern pattern, int s) :
		time(time), enemyNum(enemyNum), type(type), movePattern(movePattern),
		x(x), y(y), vx(vx), vy(vy), interval(interval), hp(hp), spread(spread), pattern(pattern),scoreValue(s){}
};
class EnemyManager
{
public:
	void init();
	void update(std::vector<enemy>& enemies, float dt);
private:
	std::vector<SpawnEntry>spawnList;
	int nextIndex;
	float timer;
	int gonenum;
	float gap;
};