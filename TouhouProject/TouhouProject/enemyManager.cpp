#include "enemyManager.h"
void EnemyManager::init()
{
	spawnList.clear();
	nextIndex = 0,timer = 0;
	gonenum = 0,gap = 0;
	BulletPattern p1 = { 0, 3, 200, 1.5f, 0, 1, 8, 14 };
	BulletPattern p2 = { -1, 0, 0,0, 0, 0, 0, 0 };
	spawnList.push_back(SpawnEntry(1.0f, 1, 0, 0, 310.0f, -30.0f, 0, 150.0f, 0, 5, 0,p1));
	spawnList.push_back(SpawnEntry(3.0f, 3, 0, 0, 200.0f, -30.0f, 0, 160.0f, 0, 5, 120,p1));
	spawnList.push_back(SpawnEntry(5.0f, 5, 1, 1, 150.0f, -30.0f, 0, 140.0f, 0.5f, 3, 0, p2));
	spawnList.push_back(SpawnEntry(7.0f, 5, 1, 1, 440.0f, -30.0f, 0, 140.0f, 0.5f, 3, 0, p2));
	spawnList.push_back(SpawnEntry(10.0f, 3, 0, 0, 310.0f, -30.0f, 0, 200.0f, 0.5f, 5, 400, p1));
}
void EnemyManager::update(std::vector<enemy>& enemies, float dt) {
	timer += dt;
	while (nextIndex < (int)spawnList.size() && spawnList[nextIndex].time <= timer)
	{
		SpawnEntry& cur = spawnList[nextIndex];
		gap += dt;

		bool shouldSpawn = false;
		if (gonenum == 0)
		{
			shouldSpawn = true;
		}
		else if (gap >= cur.interval)
		{
			shouldSpawn = true;
			gap -= cur.interval;
		}

		if (shouldSpawn)
		{
			float spawnX = cur.x + (gonenum - (cur.enemyNum - 1) / 2.0f) * cur.spread;
			enemies.push_back(enemy(32, 30, spawnX, cur.y, cur.vx, cur.vy, cur.type, cur.hp, cur.pattern));
			gonenum++;
		}

		if (gonenum >= cur.enemyNum)
		{
			nextIndex++;
			gonenum = 0;
			gap = 0;
		}
		else
		{
			break;
		}
	}
}