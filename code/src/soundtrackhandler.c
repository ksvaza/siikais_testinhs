#include "soundtrackhandler.h"

#include <raylib.h>
#include <stddef.h>
#define Rectangle winrec
#define CloseWindow winclosewindow
#define ShowCursor winshowcursor
#include <windows.h>
#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#include <stdio.h>
#include <stdlib.h>

#include <stringutils.h>

soundtrack_t* soundtracks = nullptr;
size_t soundtrackCount = 0;

int* soundtrackQueue = nullptr;
int soundtrackQueueI = 0;

void Soundtracks_Load(const char* srcFolder) // jāpārraksta
{
    string_t filepath = String_NewC(srcFolder);
    String_AddC(&filepath, filepath, "/*.mp3"); // /*.mp3
    
    WIN32_FIND_DATA ffd;
    HANDLE hf = FindFirstFile(filepath.c_str, &ffd);
    if (hf == INVALID_HANDLE_VALUE)
    {
        printf("FindFirstFile failed\n");
        return;
    }
    else
    {
        do // lielā tautu skaitīšana
        {
            soundtrackCount++;
        }
        while (FindNextFile(hf, &ffd) != 0);

        //printf("Soundtrack count: %lld\n", soundtrackCount);

        soundtracks = (soundtrack_t*)malloc(soundtrackCount * sizeof(soundtrack_t));
        if (!soundtracks) return;
        soundtrackQueue = (int*)malloc(soundtrackCount * sizeof(int));
        if (!soundtrackQueue) return;
        soundtrackQueueI = 0;

        hf = FindFirstFile(filepath.c_str, &ffd);
        int i = 0;
        do
        {
            string_t fullFilepath = String_NewC(srcFolder);
            String_AddC(&fullFilepath, fullFilepath, "/");
            String_AddC(&fullFilepath, fullFilepath, (const char*)ffd.cFileName);
            soundtracks[i].m = LoadMusicStream((const char*)fullFilepath.c_str);
            soundtracks[i].name = String_NewC((const char*)ffd.cFileName);
            soundtracks[i].fullFilepath = fullFilepath;
            soundtrackQueue[i] = i;
            //printf("File %d: %s (%s)\n", i, ffd.cFileName, fullFilepath.c_str);
            i++;
        }
        while (FindNextFile(hf, &ffd) != 0);

        String_Terminate(filepath);
        
        FindClose(hf);
    }
}

void Soundtracks_GenerateRandomQueue()
{
    if (!soundtrackQueue)
    {
        soundtrackQueue = (int*)malloc(soundtrackCount * sizeof(int));
        if (!soundtrackQueue) return;
    }

    int* temp = LoadRandomSequence(soundtrackCount, 0, soundtrackCount - 1);
    for (int  i = 0; i < (int)soundtrackCount; i++)
    {
        soundtrackQueue[i] = temp[i];
    }
    UnloadRandomSequence(temp);

    soundtrackQueueI = 0;
}

void Soundtracks_Start(int startingI)
{
    if (soundtrackCount && soundtrackQueue && soundtracks)
    {
        soundtrackQueueI = startingI % soundtrackCount;
        if (IsMusicValid(soundtracks[soundtrackQueue[soundtrackQueueI]].m)) PlayMusicStream(soundtracks[soundtrackQueue[soundtrackQueueI]].m);
    }
}

void Soundtracks_Next()
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (IsMusicValid(m)) StopMusicStream(m);
    }
    else return;

    soundtrackQueueI++;
    if ((size_t)soundtrackQueueI >= soundtrackCount) soundtrackQueueI = 0;

    m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
    if (IsMusicValid(m)) PlayMusicStream(m);
    else return;
}
void Soundtracks_Last()
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (IsMusicValid(m)) StopMusicStream(m);
    }
    else return;

    soundtrackQueueI--;
    if (soundtrackQueueI < 0) soundtrackQueueI = (int)soundtrackCount;

    m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
    if (IsMusicValid(m)) PlayMusicStream(m);
}

char soundtrack_paused = 0;
void Soundtracks_Pause()
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (IsMusicValid(m))
        {
            PauseMusicStream(m);
            soundtrack_paused = 1; 
        }
    }
}
void Soundtracks_Resume()
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (IsMusicValid(m))
        {
            ResumeMusicStream(m);
            soundtrack_paused = 0; 
        }
    }
}
char Soundtracks_GetPauseState()
{
    return soundtrack_paused;
}
void Soundtracks_TogglePause()
{
    if (soundtrack_paused) Soundtracks_Resume();
    else Soundtracks_Pause();
}

Taimeris_t* soundtrackUpdateTimer = nullptr;
Soundtracks_ReturnValue Soundtracks_Update(laiks_t currentTime)
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (IsMusicValid(m)) UpdateMusicStream(m);
        else return SOUNDTRACKS_DEFAULT;
    }
    else return SOUNDTRACKS_DEFAULT;
    
    if (!soundtrackUpdateTimer)
    {
        soundtrackUpdateTimer = (Taimeris_t*)malloc(sizeof(Taimeris_t));
        if (!soundtrackUpdateTimer) return SOUNDTRACKS_DEFAULT;
        InitTimer(soundtrackUpdateTimer, Laiks_Milliseconds(500.0f), true, false);
    }

    if (CheckTimer(soundtrackUpdateTimer, currentTime))
    {
        if (GetMusicTimeLength(m) - GetMusicTimePlayed(m) <= Laiks_InSeconds(soundtrackUpdateTimer->period) * 2.0f)
        {
            Soundtracks_Next();
            return SOUNDTRACKS_NEXT;
        }
        return SOUNDTRACKS_UPDATE;
    }

    return SOUNDTRACKS_DEFAULT;
}

float Soundtracks_GetCurrentLength()
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (!IsMusicValid(m)) return -1.0f;
    }
    else return -1.0f;

    return GetMusicTimeLength(m);
}
float Soundtracks_GetCurrentPlaytime()
{
    Music m;
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        m = soundtracks[soundtrackQueue[soundtrackQueueI]].m;
        if (!IsMusicValid(m)) return -1.0f;
    }
    else return -1.0f;

    return GetMusicTimePlayed(m);
}

int Soundtracks_GetCurrentI()
{
    return soundtrackQueueI;
}
size_t Soundtracks_GetTotalI()
{
    return soundtrackCount;
}

soundtrack_t Soundtracks_GetCurrentTrack()
{
    soundtrack_t t = (soundtrack_t){};
    if (soundtrackCount && soundtrackQueue && soundtracks) 
    {
        t = soundtracks[soundtrackQueue[soundtrackQueueI]];
        if (!IsMusicValid(t.m)) return (soundtrack_t){};
    }
    return t;
}