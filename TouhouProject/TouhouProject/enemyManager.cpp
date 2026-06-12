#include "enemyManager.h"
void EnemyManager::init()
{
	spawnList.clear();
	nextIndex = 0, timer = 0;
	gonenum = 0, gap = 0;
	BulletPattern p1 = { 0, 3, 200, 1.5f, 0, 1, 16, 16};//小怪自机弹
	BulletPattern p2 = { 1, 5, 150 ,2.0f, 5, 1, 16, 16 };//小怪扇形弹
	BulletPattern p3 = { 2, 12, 150 ,2.0f, 30, 1, 16, 16 };//小怪园形弹
	spawnList.push_back(SpawnEntry(1.0f, 1, 0, 0, 310.0f, -30.0f, 0, 150.0f, 0, 5, 0, p1,100));
	spawnList.push_back(SpawnEntry(3.0f, 3, 0, 0, 200.0f, -30.0f, 0, 160.0f, 0, 5, 120, p1,100));
	spawnList.push_back(SpawnEntry(5.0f, 5, 1, 1, 150.0f, -30.0f, 0, 120.0f, 1.0f, 3, 0, p2,300));
	spawnList.push_back(SpawnEntry(7.0f, 5, 1, 1, 440.0f, -30.0f, 0, 120.0f, 1.0f, 3, 0, p2,300));
	spawnList.push_back(SpawnEntry(10.0f, 3, 0, 0, 310.0f, -30.0f, 0, 140.0f, 1.0f, 5, 150, p3,100));
}
void EnemyManager::update(std::vector<enemy>& enemies, float dt) {
	timer += dt;
	while (nextIndex < (int)spawnList.size() && spawnList[nextIndex].time <= timer)
	{
		SpawnEntry& cur = spawnList[nextIndex];
		gap += dt;

		bool shouldSpawn = false;
		if (gonenum == 0)//该批次第一个
		{
			shouldSpawn = true;
		}
		else if (gap >= cur.interval)//大于间隔
		{
			shouldSpawn = true;
			gap -= cur.interval;
		}

		if (shouldSpawn)
		{
			float spawnX = cur.x + (gonenum - (cur.enemyNum - 1) / 2.0f) * cur.spread; 
			enemies.push_back(enemy(32, 30, spawnX, cur.y, cur.vx, cur.vy, cur.type, cur.hp, cur.pattern,cur.scoreValue));
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