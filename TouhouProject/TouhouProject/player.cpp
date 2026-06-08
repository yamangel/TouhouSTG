#include "Player.h"
#include "resource.h"
#include <Windows.h>

void updatePlayer(player& p, float dt) {
	if (p.hp <= 0) return;
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
	if (p.x + p.width / 2.0f > 640) p.x = 640 - p.width / 2.0f;
	if (p.y - p.high / 2.0f < 0)   p.y = p.high / 2.0f;
	if (p.y + p.high / 2.0f > 960) p.y = 960 - p.high / 2.0f;
}
void drawPlayer(const player& p)
{
	if (p.hp <= 0)
	{
		outtextxy(300, 250, L"GAME OVER");
		return;
	}
	putimage((int)p.x - p.width / 2,
		(int)p.y - p.high / 2,
		p.width, p.high, &imgPlayer00, p.frame * p.width, p.facing * p.high);
}
