#pragma once
#include <graphics.h>

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