#include "Sound.h"
#include <mmsystem.h>
#include <cwchar>
#pragma comment(lib, "winmm.lib")

static const wchar_t* sndNames[SND_COUNT] =
{
    L"se_tan00.wav",
    L"se_enep00.wav",
    L"se_damage00.wav",
    L"se_cardget.wav",
    L"se_item00.wav",
    L"se_ok00.wav",
    L"se_pldead00.wav",
    L"se_changeitem.wav",
};

void initSounds()
{
    wchar_t cwd[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, cwd);

    for (int i = 0; i < SND_COUNT; i++)
    {
        wchar_t fullPath[MAX_PATH], alias[16], cmd[1024];
        swprintf_s(fullPath, MAX_PATH, L"%s\\MUSIC\\%s", cwd, sndNames[i]);
        swprintf_s(alias, 16, L"snd%d", i);
        swprintf_s(cmd, 1024, L"open \"%s\" type waveaudio alias %s",
            fullPath, alias);
        mciSendString(cmd, NULL, 0, NULL);
    }
}

void playSE(SoundID id, int volume)
{
    if (id < 0 || id >= SND_COUNT) return;

    wchar_t alias[16], cmd[512];
    swprintf_s(alias, 16, L"snd%d", id);
    swprintf_s(cmd, 512, L"play %s from 0", alias);
    mciSendString(cmd, NULL, 0, NULL);
}
void playBGM(const wchar_t* filename, int volume)
{
    (void)volume;
    wchar_t cwd[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, cwd);
    wchar_t fullPath[MAX_PATH];
    swprintf_s(fullPath, MAX_PATH, L"%s\\MUSIC\\%s", cwd, filename);

    PlaySound(fullPath, NULL,
        SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
}

void stopBGM()
{
    PlaySound(NULL, NULL, 0);
}
