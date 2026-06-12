#include "resource.h"
#include "background.h"

void initBackground(Background& bg, const wchar_t* path, float speed, int t)
{
	if (t == 0)//±≥æ∞
	{
		loadimage(&bg.img, path, 640, 960, true);
		bg.y[0] = 0, bg.y[1] = -960;
		bg.speed = speed;
		bg.type = t;
	}
	if (t == 1)//‘∆
	{
		loadimage(&bg.img, path, 640, 480, true);
		bg.y[0] = 0, bg.y[1] = -480, bg.y[2] = -960;
		bg.speed = speed;
		bg.type = t;
		bg.srcW = bg.img.getwidth();
		bg.srcH = bg.img.getheight();
	}
	if (t == -1)//end//yµ±x π”√
	{
		loadimage(&bg.img, path);
		bg.y[0] = 0, bg.y[1] = 2122;
		bg.speed = speed;
		bg.type = t;
	}
}
void updateBackground(Background& bg, float dt)
{
	if (bg.type == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			bg.y[i] += dt * bg.speed;
			if (bg.y[i] >= 960)
			{
				bg.y[i] -= 1920;
			}
		}
	}
	if (bg.type == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			bg.y[i] += dt * bg.speed;
			if (bg.y[i] >= 960)
			{
				bg.y[i] -= 1440;
			}
		}
	}
	if (bg.type == -1)
	{
		for (int i = 0; i < 2; i++)
		{
			bg.y[i] -= dt * bg.speed;
			if (bg.y[i] <= -2122)
			{
				bg.y[i] += 4244;
			}
		}
	}
}
void drawBackground(Background& bg)
{
	if (bg.type == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			putimage(0, bg.y[i], 640, 960, &bg.img, 0, 0);
		}
	}
	if (bg.type == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			putimage(0, bg.y[i], 640, 480, &cloud, 0, 0, SRCAND);
			putimage(0, bg.y[i], 640, 480, &bg.img, 0, 0, SRCPAINT);
		}
	}
	if (bg.type == -1)
	{
		for (int i = 0; i < 2; i++)
		{
			putimage(bg.y[i], 0, &bg.img);
		}
	}
}