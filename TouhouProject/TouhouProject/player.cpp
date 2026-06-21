#include "player.h"
#include "resource.h"
#include "bullet.h"
#include <Windows.h>

void updatePlayer(player& p, float dt) {
	float speed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? p.slowspeed : p.speed;
	bool left = GetAsyncKeyState(VK_LEFT) & 0x8000;
	bool right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	if (left && !right)//向左移动
	{
		p.x -= speed * dt;
		if (p.facing != 1) p.frame = 0;
		p.facing = 1;
	}
	else if (right && !left)//向右移动
	{
		p.x += speed * dt;
		if (p.facing != 2) p.frame = 0;
		p.facing = 2;
	}
	else
	{
		if (p.facing != 0) p.frame = 0;
		p.facing = 0;
	}

	if (p.invincibleTimer > 0) p.invincibleTimer -= dt;//无敌时间
	p.frameTimer += dt;//动画帧切换
	if (p.frameTimer > 0.1f)
	{
		p.frame = (p.frame + 1) % 8;
		p.frameTimer -= 0.1f;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) p.y -= speed * dt;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) p.y += speed * dt;

	if (p.x - p.width / 2.0f < 0)   p.x = p.width / 2.0f;//边界检测
	if (p.x + p.width / 2.0f > 832) p.x = 832 - p.width / 2.0f;
	if (p.y - p.high / 2.0f < 0)   p.y = p.high / 2.0f;
	if (p.y + p.high / 2.0f > 960) p.y = 960 - p.high / 2.0f;
}
void drawPlayer(const player& p)
{
	putimage((int)p.x - p.width / 2,
		(int)p.y - p.high / 2,
		p.width, p.high, &imgPlayer00white, p.frame * p.width, p.facing * p.high, NOTSRCERASE);
	putimage((int)p.x - p.width / 2,
		(int)p.y - p.high / 2,
		p.width, p.high, &imgPlayer00, p.frame * p.width, p.facing * p.high, SRCINVERT);
}
void drawplayerCollisions(player& player, std::vector<Bullet>& enemyBullets)
{
	for (auto& b : enemyBullets)
	{
		float inX = fabs(player.x - b.x);
		float inY = fabs(player.y - b.y);
		if (inX < 28 || inY < 33)
		{
			putimage(player.x - b.width / 2 + 1, player.y - b.high / 2 + 1, b.width, b.high, &imgEnemyBulletwhite, 82, 242, NOTSRCERASE);
			putimage(player.x - b.width / 2 + 1, player.y - b.high / 2 + 1, b.width, b.high, &imgEnemyBullet, 82, 242, SRCINVERT);
		}
	}
}
