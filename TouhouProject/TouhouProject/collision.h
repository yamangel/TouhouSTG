#pragma once
#include "bullet.h"
#include "enemy.h"
#include "player.h"

void checkCollisions(player& player, std::vector<Bullet>& bullets,
	std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets,int& score, float& power);