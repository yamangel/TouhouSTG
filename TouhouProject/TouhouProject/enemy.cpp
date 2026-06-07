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
void drawEnemy(const std::vector<enemy>& enemies)//32,30,0,320
{
	for (const enemy& e : enemies)
	{
		if (e.alive == true)
		{
			putimage((int)e.x - e.width / 2, (int)e.y - e.high / 2, e.width, e.high, &imgEnemy00, e.state * 128 + e.frame * 32, 320 + e.type * 32);
		}
	}
}