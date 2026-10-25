#include "dziivnieku_ferma.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <raymath.h>

#include <stringutils.h>

animal_base_t** DZIIVNIEKU_FERMA = nullptr;

int DZIIVNIEKU_FERMAS_IZMEERS = 8;
int DZIIVNIEKU_FERMAS_DZIIVNIEKU_SKAITS = 16;

Colour ferma_GenRandomColour()
{
    switch (GetRandomValue(1, 21))
        {
        case 1:
            return LIGHTGRAY;
        case 2:
            return GRAY;
        case 3:
            return DARKGRAY;
        case 4:
            return YELLOW;
        case 5:
            return GOLD;
        case 6:
            return ORANGE;
        case 7:
            return PINK;
        case 8:
            return RED;
        case 9:
            return MAROON;
        case 10:
            return GREEN;
        case 11:
            return LIME;
        case 12:
            return DARKGREEN;
        case 13:
            return RAYWHITE; // SKYBLUE
        case 14:
            return BLUE;
        case 15:
            return DARKBLUE;
        case 16:
            return PURPLE;
        case 17:
            return VIOLET;
        case 18:
            return DARKPURPLE;
        case 19:
            return BEIGE;
        case 20:
            return BROWN;
        case 21:
            return DARKBROWN;
        }
}

Vector3* DZIIVNIEKU_FERMA_UNIQUEPOSTABLE = nullptr;
size_t DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_I = 0;
size_t DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_SIZE = 0;
Vector3 DZIIVNIEKU_FERMA_UNIQUEPOS_BOXBOTTOM = {};
Vector3 DZIIVNIEKU_FERMA_UNIQUEPOS_BOXTOP = {};
Vector3 DZIIVNIEKU_FERMA_UNIQUEPOS_DIVVEC = {};
void ferma_SetupUniquePositionTable(size_t size, Vector3 boxBottom, Vector3 boxTop, Vector3 divvec)
{
    if (DZIIVNIEKU_FERMA_UNIQUEPOSTABLE) free(DZIIVNIEKU_FERMA_UNIQUEPOSTABLE);
    DZIIVNIEKU_FERMA_UNIQUEPOSTABLE = (Vector3*)malloc(size * sizeof(Vector3));
    if (!DZIIVNIEKU_FERMA_UNIQUEPOSTABLE) return;
    
    memset(DZIIVNIEKU_FERMA_UNIQUEPOSTABLE, 0, size * sizeof(Vector3));
    DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_I = 0;
    DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_SIZE = size;
    DZIIVNIEKU_FERMA_UNIQUEPOS_BOXBOTTOM = boxBottom;
    DZIIVNIEKU_FERMA_UNIQUEPOS_BOXTOP = boxTop;
    DZIIVNIEKU_FERMA_UNIQUEPOS_DIVVEC = divvec;
}
bool ferma_IsUniquePositionInTable(Vector3 pos)
{
    if (!DZIIVNIEKU_FERMA_UNIQUEPOSTABLE) return false;

    for (size_t i = 0; i < DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_SIZE; i++)
    {
        if (Vector3Equals(pos, DZIIVNIEKU_FERMA_UNIQUEPOSTABLE[i])) return false;
    }

    return true;
}
Vector3 ferma_GenRandomPosition()
{
    Vector3 bb = DZIIVNIEKU_FERMA_UNIQUEPOS_BOXBOTTOM;
    Vector3 bt = DZIIVNIEKU_FERMA_UNIQUEPOS_BOXTOP;
    Vector3 dv = DZIIVNIEKU_FERMA_UNIQUEPOS_DIVVEC;
    return (Vector3)
    {
        dv.x != 0.0f ? (float)(GetRandomValue(0, (int)((bt.x - bb.x) / dv.x))) * dv.x + bb.x : 0.0f,
        dv.y != 0.0f ? (float)(GetRandomValue(0, (int)((bt.y - bb.y) / dv.y))) * dv.y + bb.y : 0.0f,
        dv.z != 0.0f ? (float)(GetRandomValue(0, (int)((bt.z - bb.z) / dv.z))) * dv.z + bb.z : 0.0f
    };
}
bool ferma_GenUniquePosition(Vector3* v)
{
    if (!v || !DZIIVNIEKU_FERMA_UNIQUEPOSTABLE) return false;

    Vector3 nv = ferma_GenRandomPosition();

    for (size_t i = 0; !ferma_IsUniquePositionInTable(nv); i++)
    {
        if (i >= DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_SIZE) return false;
        nv = ferma_GenRandomPosition();
    }
    DZIIVNIEKU_FERMA_UNIQUEPOSTABLE[DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_I] = nv;
    DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_I++;
    if (DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_I >= DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_SIZE) DZIIVNIEKU_FERMA_UNIQUEPOSTABLE_I = 0;
    *v = nv;
    return true;
}

void Ferma_Generate(int fermas_izmeers, int dziivnieku_skaits)
{
    DZIIVNIEKU_FERMAS_IZMEERS = fermas_izmeers;
    if (fermas_izmeers * fermas_izmeers < dziivnieku_skaits) dziivnieku_skaits = fermas_izmeers * fermas_izmeers;
    DZIIVNIEKU_FERMAS_DZIIVNIEKU_SKAITS = dziivnieku_skaits;

    animal_base_t** dfp = DZIIVNIEKU_FERMA;
    if (dfp) free(dfp);
    
    dfp = (animal_base_t**)malloc(dziivnieku_skaits * sizeof(animal_base_t*));
    if (!dfp) return;
    memset(dfp, 0, dziivnieku_skaits * sizeof(animal_base_t*));

    ferma_SetupUniquePositionTable
    (
        fermas_izmeers * fermas_izmeers,
        (Vector3){ ((float)-fermas_izmeers + 1) / 2.0f, 0.0f, ((float)-fermas_izmeers + 1) / 2.0f },
        (Vector3){ ((float)fermas_izmeers - 1) / 2.0f, 0.0f, ((float)fermas_izmeers - 1) / 2.0f },
        (Vector3){ 1.0f, 0.0f, 1.0f }
    );

    for (int i = 0; i < dziivnieku_skaits / 2; i++)
    {
        Vector3 pos = {};
        if (!ferma_GenUniquePosition(&pos)) break;

        kraasains_dziivnieks_t* k = Animal_Kraasains_Create
        (
            String_TempC("Jaaniitis"),
            pos,
            ferma_GenRandomColour()
        );

        dfp[i] = (animal_base_t*)k;
    }

    for (int i = dziivnieku_skaits / 2; i < dziivnieku_skaits; i++)
    {
        Vector3 pos = {};
        if (!ferma_GenUniquePosition(&pos)) break;

        gars_dziivnieks_t* g = Animal_Gars_Create
        (
            String_TempC("Braaliitis"),
            pos,
            (float)(GetRandomValue(200, 1500)) / 1000.0f
        );
        
        dfp[i] = (animal_base_t*)g;
    }

    DZIIVNIEKU_FERMA = dfp;
    return;
}

Taimeris_t DZIIVNIEKU_FERMA_UPDATE_TIMER = {};
void Ferma_Update(laiks_t currentTime)
{
    if (!DZIIVNIEKU_FERMA_UPDATE_TIMER.enabled) InitTimer(&DZIIVNIEKU_FERMA_UPDATE_TIMER, Laiks_Milliseconds(10.0f), true, false);
    if (CheckTimer(&DZIIVNIEKU_FERMA_UPDATE_TIMER, currentTime))
    {
        animal_base_t** dfp = DZIIVNIEKU_FERMA;
        if (!dfp) return;

        for (int i = 0; i < DZIIVNIEKU_FERMAS_DZIIVNIEKU_SKAITS; i++)
        {
            if (dfp[i] && dfp[i]->age) dfp[i]->age(dfp[i], currentTime);
        }
    }
}

void Ferma_Draw()
{
    animal_base_t** dfp = DZIIVNIEKU_FERMA;
    if (!dfp) return;

    DrawGrid(DZIIVNIEKU_FERMAS_IZMEERS, 1.0f);

    for (int i = 0; i < DZIIVNIEKU_FERMAS_DZIIVNIEKU_SKAITS; i++)
    {
        if (dfp[i] && dfp[i]->draw) dfp[i]->draw(dfp[i]);
    }
}


animal_base_t* DZIIVNIEKU_FERMA_CURRENT_HIT = nullptr;
animal_base_t* Ferma_CheckRay(Ray ray)
{
    animal_base_t** dfp = DZIIVNIEKU_FERMA;
    if (!dfp) return nullptr;

    RayCollision c = {}; bool f = false; int ci = 0;
    for (int i = 0; i < DZIIVNIEKU_FERMAS_DZIIVNIEKU_SKAITS; i++)
    {
        if (!dfp[i] || !dfp[i]->checkRay) continue;

        RayCollision t = dfp[i]->checkRay(dfp[i], ray);
        if (t.hit)
        {
            if (!f)
            {
                c = t;
                ci = i;
                f = true;
            }
            else if (t.distance < c.distance)
            {
                c = t;
                ci = i;
            }
        }
    }
    if (!f || !dfp[ci]) // return nullptr;
    {
        if (DZIIVNIEKU_FERMA_CURRENT_HIT) DZIIVNIEKU_FERMA_CURRENT_HIT->deselect(DZIIVNIEKU_FERMA_CURRENT_HIT);
        DZIIVNIEKU_FERMA_CURRENT_HIT = nullptr;
        return nullptr;
    }

    if (DZIIVNIEKU_FERMA_CURRENT_HIT != dfp[ci]) 
    {
        if (DZIIVNIEKU_FERMA_CURRENT_HIT) DZIIVNIEKU_FERMA_CURRENT_HIT->deselect(DZIIVNIEKU_FERMA_CURRENT_HIT);
        dfp[ci]->select(dfp[ci]);
        DZIIVNIEKU_FERMA_CURRENT_HIT = dfp[ci];
    }

    return dfp[ci];
}
