#include"enemy.h"
#include "resource.h"
#include <cmath>
void updateEnemy(std::vector<enemy>& enemies, float dt)
{
	for (auto& e : enemies)
	{
		if (e.type == 0)
		{
			e.y += e.vy * dt;
		}
		else if (e.type == 1)
		{
			e.x += 200 * sin(e.y / 50) * dt;
			e.y += e.vy * dt;
		}
		if (e.x < -36 || e.x>672 || e.y > 990)
		{
			e.alive = false;
		}
		if (e.hp <= 0)
		{
			e.alive = false;
		}
	}
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](enemy& e) { return !e.alive; }), enemies.end());
}
void drawEnemy(const std::vector<enemy>& enemies)
{
	for (const enemy& e : enemies)
	{
		if (e.alive == true)
		{
			putimage((int)e.x - e.width / 2, (int)e.y - e.high / 2, e.width, e.high, &imgEnemy00, e.state * 128 + e.frame * 32, 320 + e.type * 32);
		}
	}
}
void enemysetup(std::vector<enemy>& enemies, clock_t now)//32,30,0,320
{
	static int times = 0;
	if ((now / CLOCKS_PER_SEC) == 3 && times == 0)
	{
		enemies.push_back(enemy(32, 30, 320, -30, 150.0f, 150.0f, 0, 3));
		enemies.push_back(enemy(32, 30, 320, -105, 150.0f, 150.0f, 0, 3));
		enemies.push_back(enemy(32, 30, 320, -180, 150.0f, 150.0f, 0, 3));
		times++;
	}
	if (((now / CLOCKS_PER_SEC) >= 5) && ((now / CLOCKS_PER_SEC) <= 10) && ((now / CLOCKS_PER_SEC) % 1 == 0) && times == 1)
	{
		enemies.push_back(enemy(32, 30, 215, -30, 150.0f, 150.0f, 1, 3));
		enemies.push_back(enemy(32, 30, 215, -105, 150.0f, 150.0f, 1, 3));
		enemies.push_back(enemy(32, 30, 430, -30, 150.0f, 150.0f, 1, 3));
		enemies.push_back(enemy(32, 30, 430, -105, 150.0f, 150.0f, 1, 3));
		times++;
	}
}