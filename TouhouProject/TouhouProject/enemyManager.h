#pragma once
#include <vector>
#include "Enemy.h"

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
	SpawnEntry(float time, int enemyNum, int type, int movePattern, float x, float y, float vx, float vy, float interval, int hp, float spread) :
		time(time), enemyNum(enemyNum), type(type), movePattern(movePattern), x(x), y(y), vx(vx), vy(vy), interval(interval), hp(hp), spread(spread) {
	}
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