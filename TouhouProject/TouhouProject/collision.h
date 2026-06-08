#pragma once
#include "bullet.h"
#include "enemy.h"
#include "player.h"

void checkCollisions(player& p, std::vector<Bullet>& bullets, std::vector<enemy>& enemies);