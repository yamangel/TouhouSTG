#pragma once
#include <vector>

class Bullet {
public:
	Bullet(int w, int h, float x, float y, float vx, float vy, int type) :width(w), high(h), x(x), y(y), vx(vx), vy(vy), type(type) {}
	bool alive = true;
	float x, y;
	float vx, vy;
	int width, high;
	int type;
};
void updateBullets(std::vector<Bullet>& bullets, float dt);
void drawBullets(const std::vector<Bullet>& bullets);
void shoot(std::vector<Bullet>& bullets, int width, int high, float x, float y, int count, float baseAngle, float spreadAngle, float speed, int type);