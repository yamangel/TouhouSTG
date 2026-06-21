#pragma once
#include <Windows.h>

enum SoundID
{
    SND_SHOOT,
    SND_ENEMY,
    SND_DAMAGE,
    SND_BOMB,
    SND_ITEM,
    SND_OK,
    SND_DEAD,
    SND_SELECT,
    SND_COUNT
};

void initSounds();
void playSE(SoundID id, int volume = 500);
void playBGM(const wchar_t* filename, int volume = 800);
void stopBGM();
