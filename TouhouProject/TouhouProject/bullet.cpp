#include "Bullet.h"
#include "resource.h"
#include <graphics.h>

void updateBullets(std::vector<Bullet>& bullets, float dt)
{
	for (Bullet& b : bullets)
	{
		b.x += b.vx * dt;
		b.y += b.vy * dt;
		if (b.y < 0)
		{
			b.alive = false;
		}
		if (b.x < -36 || b.x>832 || b.y > 990)//离开窗口判定死亡（游戏区832）
		{
			b.alive = false;
		}
	}
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return !b.alive; }), bullets.end());
}

void drawBullets(const std::vector<Bullet>& bullets)
{
	for (const Bullet& b : bullets)
	{
		if (b.alive) {
			if (b.type == 0)//灵梦基础弹
			{
				putimage((int)b.x - b.width / 2,
					(int)b.y - b.high / 2,
					b.width, b.high, &imgBullet00white, 146, 1, NOTSRCERASE);
				putimage((int)b.x - b.width / 2,
					(int)b.y - b.high / 2,
					b.width, b.high, &imgBullet00, 146, 1, SRCINVERT);
			}
			if (b.type == 2)//旋转弹
			{
				putimage((int)b.x - b.width / 2,
					(int)b.y - b.high / 2,
					b.width, b.high, &imgEnemyBulletwhite, 147, 65, NOTSRCERASE);
				putimage((int)b.x - b.width / 2,
					(int)b.y - b.high / 2,
					b.width, b.high, &imgEnemyBullet, 147, 65, SRCINVERT);
			}
			if (b.type == 1) //小怪子弹
			{
				putimage((int)b.x - b.width / 2,
					(int)b.y - b.high / 2,
					b.width, b.high, &imgEnemyBulletwhite, 80, 48, NOTSRCERASE);
				putimage((int)b.x - b.width / 2,
					(int)b.y - b.high / 2,
					b.width, b.high, &imgEnemyBullet, 80, 48, SRCINVERT);
			}
		}
	}
}

void shoot(std::vector<Bullet>& bullets, int width, int high, float x, float y, int count, float baseAngle, float spreadAngle, float speed, int type)
{
	bullets.push_back(Bullet(width, high, x, y, 0, -speed, type));
	for (int i = 1; i < (count + 1) / 2; i++)
	{
		float rad = (baseAngle + i * spreadAngle) * 3.14159265f / 180.0f;
		float vx = speed * cos(rad), vy = -speed * sin(rad);
		bullets.push_back(Bullet(width, high, x, y, vx, vy, type));
		bullets.push_back(Bullet(width, high, x, y, -vx, vy, type));
	}
}