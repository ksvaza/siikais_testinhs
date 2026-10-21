#ifndef SOUNDTRACKHANDLER_H
#define SOUNDTRACKHANDLER_H

#include <raylib.h>
#include <stringutils.h>
#include <laiks.h>
#include <stddef.h>

typedef enum {
    SOUNDTRACKS_DEFAULT = 0x00U,
    SOUNDTRACKS_UPDATE  = 0x01U,
    SOUNDTRACKS_NEXT    = 0x02U,
} Soundtracks_ReturnValue;

typedef struct
{
    Music m;
    string_t name;
    string_t fullFilepath;
} soundtrack_t;


void Soundtracks_Load(const char* srcFolder);
void Soundtracks_GenerateRandomQueue();

void Soundtracks_Start(int startingI);
Soundtracks_ReturnValue Soundtracks_Update(laiks_t currentTime);

void Soundtracks_Next();
void Soundtracks_Last();

void Soundtracks_Pause();
void Soundtracks_Resume();
char Soundtracks_GetPauseState();
void Soundtracks_TogglePause();

float Soundtracks_GetCurrentLength();
float Soundtracks_GetCurrentPlaytime();

int Soundtracks_GetCurrentI();
size_t Soundtracks_GetTotalI();

soundtrack_t Soundtracks_GetCurrentTrack();

#endif
