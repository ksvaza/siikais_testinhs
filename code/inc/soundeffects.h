#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H


#include <raylib.h>
#include <stringutils.h>
#include <stddef.h>

typedef enum 
{
    SEFF_OK        = 0x0000U,
    SEFF_FIND_FAIL = 0x0100U,
    SEFF_PLAY_FAIL = 0x0200U,
    SEFF_LOAD_FAIL = 0x0300U,
    SEFF_ADD_FAIL  = 0x0400U,
    SEFF_INIT_FAIL = 0x0500U,
} seff_error_t;

typedef struct
{
    Sound s;
    string_t* name;
} seff_sound_t;

typedef struct
{
    seff_sound_t* sounds;
    string_t* reftable;
    size_t count;
    size_t size;
} seff_library_t;

bool SoundEffect_IsError(seff_error_t e);

seff_error_t SoundEffect_InitLibrary(size_t startsize);
// unload lobrary?

seff_error_t SoundEffect_AddSound(Sound s, string_t key);
seff_error_t SoundEffect_LoadWave(const char* filepath, string_t key);
seff_error_t SoundEffect_Load(const char* filepath, string_t key);

seff_error_t SoundEffect_FindSound(seff_sound_t* s, string_t key);
seff_error_t SoundEffect_PlaySound(string_t key);


#endif
