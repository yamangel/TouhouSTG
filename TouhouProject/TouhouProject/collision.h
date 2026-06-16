#pragma once
#include "enemy.h"
#include "player.h"
#include "item.h"

void checkCollisions(player& player, std::vector<Bullet>& bullets,
	std::vector<enemy>& enemies, std::vector<Bullet>& enemyBullets, std::vector<PowerItem>& items,
	int& score);