#include"enemy.h"
#include "resource.h"
#include "bullet.h"
#include <cmath>
void updateEnemy(std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets, float playerX, float playerY, float dt)
{
	for (auto& e : enemies)
	{
		e.frameTimer += dt;//动画帧切换
		if (e.frameTimer > 0.1f)
		{
			e.frame++;
			e.frameTimer -= 0.1f;
		}

		if (e.movePattern == 0)//直线向下敌机
		{
			e.y += e.vy * dt;
			e.frame = e.frame % 4;
		}
		else if (e.movePattern == 1)//正弦波下降敌机
		{
			e.x += 100 * sin(e.y / 50) * dt;
			e.y += e.vy * dt;
			if (e.y < 150)e.frame = e.frame % 4;
			else
			{
				e.frame = e.frame % 12;
				if (e.frame < 8) e.frame = 8;
			}
		}
		//else if()//更多机型，例如悬挂出来的精英怪


		if (e.pattern.patternType >= 0) {
			e.shootTimer -= dt;
			if ((e.shootTimer <= 0) && (e.y < playerY))
			{
				float dx = playerX - e.x;
				float dy = playerY - e.y;
				float len = sqrt(dx * dx + dy * dy);
				float vx = dx / len * e.pattern.speed;
				float vy = dy / len * e.pattern.speed;//按比例分配速度，使斜向总速度控制为speed
				if (e.pattern.patternType == 0) //自机狙
				{
					for (int i = 0; i < e.pattern.bulletCount; i++) {
						enemyBullets.push_back(Bullet(e.pattern.bulletW, e.pattern.bulletH,
							e.x, e.y, vx, vy, e.pattern.bulletType));
					}
				}
				if (e.pattern.patternType == 1)//扇形狙
				{
					double baseAngle = atan2(vy, vx);
					enemyBullets.push_back(Bullet(e.pattern.bulletW, e.pattern.bulletH, e.x, e.y, vx, vy, e.pattern.bulletType));
					for (int i = 1; i < (e.pattern.bulletCount + 1) / 2; i++)
					{
						float offset = (i * e.pattern.spreadAngle) * 3.14159265f / 180.0f;
						float radleft = (baseAngle + offset);
						float radright = (baseAngle - offset);
						float vxleft = e.pattern.speed * cos(radleft), vyleft = e.pattern.speed * sin(radleft);
						float vxright = e.pattern.speed * cos(radright), vyright = e.pattern.speed * sin(radright);
						enemyBullets.push_back(Bullet(e.pattern.bulletW, e.pattern.bulletH, e.x, e.y, vxleft, vyleft, e.pattern.bulletType));
						enemyBullets.push_back(Bullet(e.pattern.bulletW, e.pattern.bulletH, e.x, e.y, vxright, vyright, e.pattern.bulletType));
					}
				}
				if (e.pattern.patternType == 2)//圆形狙
				{
					for (int i = 0; i < e.pattern.bulletCount; i++)
					{
						float rad = i * e.pattern.spreadAngle * 3.14159265f / 180.0f;
						float vx = e.pattern.speed * cos(rad);
						float vy = e.pattern.speed * sin(rad);
						enemyBullets.push_back(Bullet(e.pattern.bulletW, e.pattern.bulletH, e.x, e.y, vx, vy, e.pattern.bulletType));;
					}
				}
				e.shootTimer = e.pattern.interval;
			}
		}

		if (e.x < -36 || e.x>832 || e.y > 990)//离开窗口判定死亡（游戏区832）
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
			if (e.x <= 416)//左半用标准图
			{
				putimage((int)e.x - e.width / 2,
					(int)e.y - e.high / 2,
					e.width, e.high, &imgEnemy00white, e.frame * 32, 320 + e.type * 32, NOTSRCERASE);
				putimage((int)e.x - e.width / 2,
					(int)e.y - e.high / 2,
					e.width, e.high, &imgEnemy00, e.frame * 32, 320 + e.type * 32, SRCINVERT);
			}
			else//右半用镜像图
			{
				putimage((int)e.x - e.width / 2,
					(int)e.y - e.high / 2,
					e.width, e.high, &imgEnemy00Flippedwhite, e.frame * 32, 320 + e.type * 32, NOTSRCERASE);
				putimage((int)e.x - e.width / 2,
					(int)e.y - e.high / 2,
					e.width, e.high, &imgEnemy00Flipped, e.frame * 32, 320 + e.type * 32, SRCINVERT);
			}
		}
	}
}