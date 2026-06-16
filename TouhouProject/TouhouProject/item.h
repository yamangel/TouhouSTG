#pragma once
#include "player.h"
#include "resource.h"
struct PowerItem {
	int h, w;
	float x, y;
	float value;
	bool alive = true;
	float collectRadius = 40.0f;  // Œ¸ ’≈–∂®∞Îæ∂
	PowerItem(int h,int w,float x,float y,float value):h(h),w(w),x(x),y(y),value(value){}
};

void updateItems(std::vector<PowerItem>& items,player& player,float dt);
void drawItems(const std::vector<PowerItem>& items);