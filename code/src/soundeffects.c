#include "soundeffects.h"

#include <stdlib.h>
#include <string.h>

seff_library_t SEFF_LIBRARY = {};

bool SoundEffect_IsError(seff_error_t e)
{
    return e > SEFF_OK;
}

seff_error_t SoundEffect_InitLibrary(size_t startsize)
{
    SEFF_LIBRARY = (seff_library_t){};
    seff_library_t* l = &SEFF_LIBRARY;

    l->size = startsize;

    l->sounds = (seff_sound_t*)malloc(l->size * sizeof(seff_sound_t));
    if (!l->sounds) return SEFF_INIT_FAIL | 0x01U;
    memset(l->sounds, 0, l->size * sizeof(seff_sound_t));

    l->reftable = (string_t*)malloc(l->size * sizeof(string_t));
    if (!l->reftable) return SEFF_INIT_FAIL | 0x02U;
    memset(l->reftable, 0, l->size * sizeof(string_t));

    return SEFF_OK;
}

#include <stdio.h>

seff_error_t SoundEffect_AddSound(Sound s, string_t key)
{
    seff_library_t* l = &SEFF_LIBRARY;

    if (!l->reftable) return SEFF_ADD_FAIL;
    l->reftable[l->count] = String_NewS(key);

    l->sounds[l->count] = (seff_sound_t)
    {
        s, &l->reftable[l->count]
    };
    if (!l->sounds) return SEFF_ADD_FAIL | 0x01U;

    l->count++;
    if (l->count >= l->size)
    {
        void* temp = realloc(l->sounds, l->size * 2);
        if (!temp) return SEFF_ADD_FAIL | 0x02U;
        l->sounds = (seff_sound_t*)temp;

        temp = (string_t*)realloc(l->reftable, l->size * 2);
        if (!temp) return SEFF_ADD_FAIL | 0x03U;
        l->reftable = (string_t*)temp;

        l->size *= 2;
    }

    if (key.temp) String_Terminate(key);

    return SEFF_OK;
}

seff_error_t SoundEffect_LoadWave(const char* filepath, string_t key)
{
    Wave w = LoadWave(filepath);
    Sound s = LoadSoundFromWave(w);
    UnloadWave(w);
    if (!IsSoundValid(s)) return SEFF_LOAD_FAIL;

    return SoundEffect_AddSound(s, key);
}
seff_error_t SoundEffect_Load(const char* filepath, string_t key)
{
    Sound s = LoadSound(filepath);
    if (!IsSoundValid(s)) return SEFF_LOAD_FAIL;

    return SoundEffect_AddSound(s, key);
}

seff_error_t SoundEffect_FindSound(seff_sound_t* s, string_t key)
{
    if (!s) return SEFF_FIND_FAIL | 0x01U;

    seff_library_t* l = &SEFF_LIBRARY;
    if (!l->reftable) return SEFF_FIND_FAIL | 0x02U;
    if (!l->sounds) return SEFF_FIND_FAIL | 0x03U;

    size_t ll = 0; bool f = false;
    bool keytemp = key.temp; key.temp = false;

    for (size_t i = 0; i < l->count; i++)
    {
        if (String_Compare(l->reftable[i], key))
        {
            ll = i;
            f = true;
        }
    }
    key.temp = keytemp;
    if (!f) return SEFF_FIND_FAIL;
    *s = l->sounds[ll];
    if (key.temp) String_Terminate(key);

    return SEFF_OK;
}
seff_error_t SoundEffect_PlaySound(string_t key)
{
    seff_sound_t s = {};
    seff_error_t e = SoundEffect_FindSound(&s, key);
    if (SoundEffect_IsError(e)) return e;
    
    PlaySound(s.s);

    if (!IsSoundPlaying(s.s)) return SEFF_PLAY_FAIL;

    return SEFF_OK;
}


// "kaut kas te nav"
