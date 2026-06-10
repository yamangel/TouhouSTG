#include "resource.h"
#include <graphics.h>

IMAGE imgPlayer00;
IMAGE imgBullet00;
IMAGE imgEnemy00;
IMAGE imgEnemy00Flipped;
IMAGE imgEnemyBullet;
const wchar_t* stage01aPath;
const wchar_t* stage01bPath;
const wchar_t* stage01cPath;
const wchar_t* stage01dPath;
const wchar_t* stage01ePath;
void loadResources()
{
	loadimage(&imgPlayer00, _T("ANM/player/pl00/pl00.png"));
	loadimage(&imgBullet00, _T("ANM/player/pl00/pl00a.png"));
	loadimage(&imgEnemy00, _T("ANM/enemy/enemy.png"));
	loadimage(&imgEnemy00Flipped, _T("ANM/enemy/enemyFlip.png"));
	loadimage(&imgEnemyBullet, _T("ANM/bullet/bullet1.png"));
	stage01aPath = L"ANM/background/stage01/st01a.png";
	stage01bPath = L"ANM/background/stage01/st01b.png";
	stage01cPath = L"ANM/background/stage01/st01c.png";
	stage01dPath = L"ANM/background/stage01/st01d.png";
	stage01ePath = L"ANM/background/stage01/st01e.png";
}