#pragma once
#include <graphics.h>

struct Background {
    IMAGE img;      // 背景图
    float y[2];     // 两张图的 Y 坐标
    float speed;    // 滚动速度（像素/秒）
};

void initBackground(Background& bg, const wchar_t* path, float speed);
void updateBackground(Background& bg, float dt);
void drawBackground(const Background& bg);