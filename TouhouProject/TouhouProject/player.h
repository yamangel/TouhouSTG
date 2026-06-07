#pragma once
class player
{
public:
	player(int width, int high, float x,float y, float speed, float slowspeed) : width(width), high(high), x(x), y(y), speed(speed), slowspeed(slowspeed) {}
	int width, high;
	float x, y;
	float speed;
	float slowspeed;
	int facing = 0;
	int frame = 0;
	float frameTimer = 0.0f;
};
void updatePlayer(player& p, float dt);
void drawPlayer(const player& p);