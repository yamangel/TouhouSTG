#include "collision.h"

bool circleHit(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float dx = x1 - x2, dy = y1 - y2;
	float rSum = r1 + r2;
	return dx * dx + dy * dy <= rSum * rSum;
}

void checkCollisions(player& player, std::vector<Bullet>& bullets,
	std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets, int& score, float& power)
{
	for (auto& e : enemies)// 自机 vs 敌机
	{
		if (player.invincibleTimer > 0) continue;
		if (circleHit(player.x, player.y, player.hitRadius,
			e.x, e.y, e.hitRadius))
		{
			player.hp -= 1;
			player.invincibleTimer = 1.5f;
		}
	}
	for (auto& b : enemyBullets)// 自机 vs 子弹
	{
		if (player.invincibleTimer > 0) continue;
		if (circleHit(player.x, player.y, player.hitRadius,
			b.x, b.y, b.hitRadius))
		{
			b.alive = false;
			player.hp -= 1;
			player.invincibleTimer = 1.5f;
		}
	}
	for (auto& b : bullets)  // 子弹 vs 敌机
	{
		for (auto& e : enemies)
		{
			if (circleHit(b.x, b.y, b.hitRadius,
				e.x, e.y, e.hitRadius))
			{
				b.alive = false;
				e.hp--;
				if (e.hp <= 0) 
				{ 
					score += e.scoreValue;
					if (rand() % 100 < 60)
					{
						float drop = (rand() % 3 + 1) * 0.1f;  // 0.1, 0.2, 0.3
						power += drop;
						if (power > 4.0f) power = 4.0f;          // 不超上限
					}
				}
			}
		}
	}
}