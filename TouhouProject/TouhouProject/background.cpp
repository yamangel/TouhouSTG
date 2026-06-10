#include "background.h"

void initBackground(Background& bg, const wchar_t* path, float speed)
{
    loadimage(&bg.img, path, 640, 960, true);
    bg.y[0] = 0, bg.y[1] = -960;
    bg.speed = speed;
}
void updateBackground(Background& bg, float dt)
{
    for (int i = 0; i < 2; i++)
    {
        bg.y[i] += dt * bg.speed;
        if (bg.y[i]>=960)
        {
            bg.y[i] -= 1920;
        }
    }

}
void drawBackground(const Background& bg)
{
    for (int i = 0; i < 2; i++)
    {
        putimage(0, bg.y[i], 640, 960, &bg.img, 0, 0);
    }
}