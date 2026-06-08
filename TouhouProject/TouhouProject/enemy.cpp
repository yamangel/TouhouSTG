#include"enemy.h"
#include "resource.h"
#include <cmath>
void updateEnemy(std::vector<enemy>& enemies, float dt)
{
	for (auto& e : enemies)
	{
		e.frameTimer += dt;//动画帧切换
		if (e.frameTimer > 0.1f)
		{
			e.frame++;
			e.frameTimer -= 0.1f;
		}

		if (e.type == 0)//直线向下敌机
		{
			e.y += e.vy * dt;
			e.frame = e.frame % 4;
		}
		else if (e.type == 1)//正弦波下降敌机
		{
			e.x += 200 * sin(e.y / 50) * dt;
			e.y += e.vy * dt;
			if (e.y < 150)e.frame = e.frame % 4;
			else
			{
				e.frame = e.frame % 12;
				if (e.frame < 8) e.frame = 8;
			}
		}

		if (e.x < -36 || e.x>672 || e.y > 990)//离开窗口判定死亡
		{
			e.alive = false;
		}
		if (e.hp <= 0)//血量判定
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
			if (e.x <= 320)//左半用标准图
				putimage((int)e.x - e.width / 2, 
				(int)e.y - e.high / 2,
				e.width, e.high, &imgEnemy00, e.frame * 32, 320 + e.type * 32);
			else//右半用镜像图
				putimage((int)e.x - e.width / 2,
				(int)e.y - e.high / 2,
				e.width, e.high, &imgEnemy00Flipped, e.frame * 32, 320 + e.type * 32);
		}
	}
}