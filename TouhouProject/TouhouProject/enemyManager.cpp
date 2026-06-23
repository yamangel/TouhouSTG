#include "enemyManager.h"
void EnemyManager::init()
{
	spawnList.clear();
	nextIndex = 0, timer = 0;
	gonenum = 0, gap = 0;
	BulletPattern p1 = { 0, 1, 180, 2.0f, 0, 1, 16, 16 };//自机弹
	BulletPattern p2 = { 1, 5, 120 ,2.5f, 5, 1, 16, 16 };//扇形弹
	BulletPattern p3 = { 2, 12, 120 ,2.5f, 30, 1, 16, 16 };//圆形弹
	BulletPattern p4 = { 3, 1, 300, 0.02f, 120, 2, 10, 14 };//旋转弹

	spawnList.push_back(SpawnEntry(1.0f, 3, 0, 0, 200.0f, -30.0f, 0, 50.0f, 1.0f, 3, 0, p1, 10));
	spawnList.push_back(SpawnEntry(5.0f, 3, 0, 0, 650.0f, -30.0f, 0, 50.0f, 1.0f, 3, 0, p1, 10));
	spawnList.push_back(SpawnEntry(9.0f, 3, 0, 0, 250.0f, -30.0f, 0, 50.0f, 1.0f, 3, 0, p1, 10));
	spawnList.push_back(SpawnEntry(13.0f, 3, 0, 0, 500.0f, -30.0f, 0, 50.0f, 1.0f, 3, 0, p1, 10));

	spawnList.push_back(SpawnEntry(21.0f, 5, 1, 1, 200.0f, -30.0f, 0, 80.0f, 1.5f, 2, 0, p2, 5));
	spawnList.push_back(SpawnEntry(24.0f, 5, 1, 1, 600.0f, -30.0f, 0, 80.0f, 1.5f, 2, 0, p2, 5));

	spawnList.push_back(SpawnEntry(40.0f, 2, 0, 0, 160.0f, -30.0f, 0, 60.0f, 0.0f, 3, 60, p1, 10));
	spawnList.push_back(SpawnEntry(41.0f, 2, 0, 0, 160.0f, -30.0f, 0, 60.0f, 0.0f, 3, 60, p1, 10));
	spawnList.push_back(SpawnEntry(42.0f, 2, 0, 0, 160.0f, -30.0f, 0, 60.0f, 0.0f, 3, 60, p1, 10));
	spawnList.push_back(SpawnEntry(43.0f, 2, 0, 0, 660.0f, -30.0f, 0, 60.0f, 0.0f, 3, 60, p1, 10));
	spawnList.push_back(SpawnEntry(44.0f, 2, 0, 0, 660.0f, -30.0f, 0, 60.0f, 0.0f, 3, 60, p1, 10));
	spawnList.push_back(SpawnEntry(45.0f, 2, 0, 0, 660.0f, -30.0f, 0, 60.0f, 0.0f, 3, 60, p1, 10));

	spawnList.push_back(SpawnEntry(46.0f, 3, 0, 3, 400.0f, -30.0f, 0, 40.0f, 1.0f, 5, 150, p3, 30));

	spawnList.push_back(SpawnEntry(60.0f, 1, 2, 2, 416.0f, -50.0f, 0, 200.0f, 0.0f, 150, 0, p1, 500));
}
void EnemyManager::update(std::vector<enemy>& enemies, float dt) {
	timer += dt;
	while (nextIndex < (int)spawnList.size() && spawnList[nextIndex].time <= timer)
	{
		SpawnEntry& cur = spawnList[nextIndex];
		gap += dt;

		bool shouldSpawn = false;
		if (gonenum == 0)//该波次第一个
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
			enemies.push_back(enemy(32, 30, spawnX, cur.y, cur.vx, cur.vy, cur.type, cur.movePattern, cur.hp, cur.pattern, cur.scoreValue));
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