#pragma once
#include "player.h"
#include <graphics.h>
#include <string>

struct Background {
    IMAGE img;      // ±³¾°Í¼
    int srcW, srcH; // Ô­Í¼³¤¿í
    float y[3];     // Í¼µÄ Y ×ø±ê
    float speed;    // ¹ö¶¯ËÙ¶È£¨ÏñËØ/Ãë£©
    int type;       // 0±³¾°1ÔÆ
};

void initBackground(Background& bg, const wchar_t* path, float speed,int t);
void updateBackground(Background& bg, float dt);
void drawBackground( Background& bg);
void drawUI(int score,player& player);
void drawFloat(float num, int x, int y);
void drawText(const wchar_t* text, int x, int y);
void drawHp(player& player);