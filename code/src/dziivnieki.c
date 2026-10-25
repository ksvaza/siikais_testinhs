#include "dziivnieki.h"

#include <stdlib.h>
#include <string.h>
#include <raymath.h>

int DZIIVNIEKI_FERMAS_IZMEERS = 8;
int DZIIVNIEKI_DZIIVNIEKU_SKAITS = 16;

// int augu_skaits = 8;
// int citu_skaits = 4;

buutne_t* DZIIVNIEKI_BUUTNES = nullptr;


dziivniekerr_t Dziivnieks_Generate(int fermas_izmeers, int dziivnieku_skaits)
{
    DZIIVNIEKI_FERMAS_IZMEERS = fermas_izmeers;
    if (fermas_izmeers * fermas_izmeers < dziivnieku_skaits) dziivnieku_skaits = fermas_izmeers * fermas_izmeers;
    DZIIVNIEKI_DZIIVNIEKU_SKAITS = dziivnieku_skaits;

    buutne_t* B = DZIIVNIEKI_BUUTNES;
    if (B) free(B);
    B = (buutne_t*)malloc(fermas_izmeers * fermas_izmeers * sizeof(buutne_t));
    if (!B) return DZIIVNIEKERR_GHENEREESHANAS_KLHUUME;
    memset(B, 0, fermas_izmeers * fermas_izmeers * sizeof(buutne_t));
    for (int i = 0; i < dziivnieku_skaits; i++)
    {
        buutne_t* b = &B[i];

        b->type = ENTITY_ANIMAL;
        b->animal.age = Laiks_Seconds(0.0f);
        b->p.food_units = 1.0f;
        b->p.dead = false;
        b->animal.movement_efficiency = 10.0f;
        b->animal.food_efficiency = 1.0f;

        float xpos, zpos = 0.0f;
        pozicija:
            xpos = (float)GetRandomValue(0, fermas_izmeers - 1) - ((float)(fermas_izmeers - 1) / 2.0f);
            zpos = (float)GetRandomValue(0, fermas_izmeers - 1) - ((float)(fermas_izmeers - 1) / 2.0f);
        for (int j = 0; j < i; j++)
        {
            if
            (
                (int)(xpos + 0.5f) == (int)(B[j].p.position.x + 0.5f) &&
                (int)(zpos + 0.5f) == (int)(B[j].p.position.z + 0.5f)
            ) goto pozicija;
        }

        
        b->p.position = (Vector3){xpos, 0.4f, zpos};
        b->p.name = String_NewC("Jānis Paraudzinhsh");
        b->p.size = (Vector3){0.8f, 0.8f, 0.8f};
        
        switch (GetRandomValue(1, 21))
        {
        case 1:
            b->p.colour = LIGHTGRAY;
            break;
        case 2:
            b->p.colour = GRAY;
            break;
        case 3:
            b->p.colour = DARKGRAY;
            break;
        case 4:
            b->p.colour = YELLOW;
            break;
        case 5:
            b->p.colour = GOLD;
            break;
        case 6:
            b->p.colour = ORANGE;
            break;
        case 7:
            b->p.colour = PINK;
            break;
        case 8:
            b->p.colour = RED;
            break;
        case 9:
            b->p.colour = MAROON;
            break;
        case 10:
            b->p.colour = GREEN;
            break;
        case 11:
            b->p.colour = LIME;
            break;
        case 12:
            b->p.colour = DARKGREEN;
            break;
        case 13:
            b->p.colour = RAYWHITE; // SKYBLUE
            break;
        case 14:
            b->p.colour = BLUE;
            break;
        case 15:
            b->p.colour = DARKBLUE;
            break;
        case 16:
            b->p.colour = PURPLE;
            break;
        case 17:
            b->p.colour = VIOLET;
            break;
        case 18:
            b->p.colour = DARKPURPLE;
            break;
        case 19:
            b->p.colour = BEIGE;
            break;
        case 20:
            b->p.colour = BROWN;
            break;
        case 21:
            b->p.colour = DARKBROWN;
            break;
        }
    }

    DZIIVNIEKI_BUUTNES = B;
    return DZIIVNIEKERR_VISSOK;
}
dziivniekerr_t Dziivnieks_Draw()
{
    buutne_t* B = DZIIVNIEKI_BUUTNES;
    DrawGrid(DZIIVNIEKI_FERMAS_IZMEERS, 1.0f);
    for (int i = 0; i < DZIIVNIEKI_FERMAS_IZMEERS * DZIIVNIEKI_FERMAS_IZMEERS; i++)
    {
        buutne_t b = B[i];
        if (b.type == ENTITY_ANIMAL)
        {
            DrawCapsule
            (
                b.p.position,
                Vector3Add
                (
                    b.p.position,
                    (Vector3){0.0f, b.p.size.y, 0.0f}
                ),
                (b.p.size.x + b.p.size.z) / 4.0f,
                16, 4,
                b.p.colour
            );
        }
    }

    DZIIVNIEKI_BUUTNES = B;
    return DZIIVNIEKERR_VISSOK;
}
dziivniekerr_t Dziivnieks_CheckRay()
{

    return DZIIVNIEKERR_VISSOK;
}

void Dziivnieks_Kusteeties(dziivnieks_t* d, Vector3 virziens)
{
    float zudums = Vector3Length(virziens) / d->movement_efficiency;

    if (d->energy - zudums < 0.0f)
    {
        virziens = Vector3Scale(virziens, d->energy / zudums);
        zudums = d->energy;
    }
    d->p.position = Vector3Add(d->p.position, virziens);
    d->energy -= zudums;
}

void Dziivnieks_Eest(dziivnieks_t* d, buutne_t* eediens) // vai vēl kas?
{

}

void Dziivnieks_Kliegt(dziivnieks_t* d) // citiem vārdiem, izdvest/radīt skaņu.
{

}