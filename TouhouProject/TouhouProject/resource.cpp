#include "resource.h"
#include <graphics.h>

IMAGE imgPlayer00;
IMAGE imgBullet00;
IMAGE imgEnemy00;
void loadResources() {
    loadimage(&imgPlayer00, _T("ANM/player/pl00/pl00.png"));
    loadimage(&imgBullet00, _T("ANM/player/pl00/pl00a.png"));
    loadimage(&imgEnemy00, _T("ANM/enemy/enemy.png"));
}