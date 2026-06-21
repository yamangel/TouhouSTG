#include "resource.h"
#include "background.h"

void initBackground(Background& bg, const wchar_t* path, float speed, int t)
{
	if (t == 0)//背景
	{
		loadimage(&bg.img, path, 832, 960, true);
		bg.y[0] = 0, bg.y[1] = -960;
		bg.speed = speed;
		bg.type = t;
	}
	if (t == 1)//云
	{
		loadimage(&bg.img, path, 832, 480, true);
		bg.y[0] = 0, bg.y[1] = -480, bg.y[2] = -960;
		bg.speed = speed;
		bg.type = t;
		bg.srcW = bg.img.getwidth();
		bg.srcH = bg.img.getheight();
	}
	if (t == -1)//end//y当x用
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
			putimage(0, bg.y[i], 832, 960, &bg.img, 0, 0);
		}
	}
	if (bg.type == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			putimage(0, bg.y[i], 832, 480, &cloud, 0, 0, SRCAND);
			putimage(0, bg.y[i], 832, 480, &bg.img, 0, 0, SRCPAINT);
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

void drawFloat(float num, int x, int y)
{
	const int digitW = 32, digitH = 32, srcY = 288;
	wchar_t str[16];
	swprintf_s(str, 16, L"%.2f", num);  // 格式化成 "3.50"
	int len = (int)wcslen(str);

	for (int i = 0; i < len; i++)
	{
		wchar_t ch = str[i];
		if (ch == L'.')  // 小数点 → 在字体表里找 . 的位置画（第一行第11个，srcX=11*32=352）
		{
			putimage(x, y, digitW, digitH,
				&ascii_1280_white, 352, srcY, NOTSRCERASE);
			putimage(x, y, digitW, digitH,
				&ascii_1280, 352, srcY, SRCINVERT);
			x += digitW;
		}
		else  // 数字 0-9，和原来一样
		{
			int digit = ch - L'0';
			int srcX = digit * digitW;
			putimage(x, y, digitW, digitH,
				&ascii_1280_white, srcX, srcY, NOTSRCERASE);
			putimage(x, y, digitW, digitH,
				&ascii_1280, srcX, srcY, SRCINVERT);
			x += digitW;
		}
	}
}

void drawText(const wchar_t* text, int x, int y)
{
	const int charW = 28;
	const int charH = 28;
	const int charsPerRow = 18;

	std::wstring table;
	table += L"!\"";
	table += L'#';                         // ← 单独加 #，避开预处理器
	table += L"$%&'（）*+，-./01";
	table += L"23456789:;《=》?@ABC";
	table += L"DEFGHIJKLMNOPQRSTU";
	table += L"VWXYZ[\\]^_ abcdefg";
	table += L"hijklmnopqrstuvwxy";

	const wchar_t* tbl = table.c_str();

	int len = (int)wcslen(text);
	for (int i = 0; i < len; i++)
	{
		wchar_t ch = text[i];

		// 在字符表中查找
		const wchar_t* pos = wcschr(tbl, ch);
		if (!pos)
		{
			// 找不到的字符就跳过（画一个空格的距离）
			x += charW;
			continue;
		}

		// 计算在精灵图中的行列
		int index = (int)(pos - tbl);
		int col = index % charsPerRow;
		int row = index / charsPerRow;

		int srcX = col * charW;
		int srcY = row * charH;
		putimage(x, y, charW, charH,
			&ascii_1280_white, srcX, srcY, NOTSRCERASE);
		putimage(x, y, charW, charH,
			&ascii_1280, srcX, srcY, SRCINVERT);

		x += charW;  // 光标右移
	}
}

void drawHp(player& player)
{
	int heartSrcX = 992, heartSrcY = 0;
	int heartW = 35, heartH = 32;
	for (int i = 0; i < player.hp; i++)
	{
		putimage(870 + i * (heartW + 4), 200, heartW, heartH,
			&front00_white, heartSrcX, heartSrcY, NOTSRCERASE);
		putimage(870 + i * (heartW + 4), 200, heartW, heartH,
			&front00, heartSrcX, heartSrcY, SRCINVERT);
	}
}

void drawUI(int score, player& player)
{
	putimage(832, 0, 448, 960, &front00_white, 64, 0, NOTSRCERASE);
	putimage(832, 0, 448, 960, &front00, 64, 0, SRCINVERT);
	drawText(L"Score:", 870, 100);
	drawFloat(score, 1030, 100);
	putimage(870, 150, 100, 30, &front00_white, 660, 110, NOTSRCERASE);
	putimage(870, 150, 100, 30, &front00, 660, 110, SRCINVERT);
	drawFloat(player.power, 1030, 150);
	drawHp(player);
}