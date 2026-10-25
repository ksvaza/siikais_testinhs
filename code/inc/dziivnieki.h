#ifndef DZIIVNIEKI_H
#define DZIIVNIEKI_H


#include <laiks.h>
#include <raylib.h>
#include <stringutils.h>

typedef enum 
{
    ENTITY_NULL   = 0x00U,
    ENTITY_ANIMAL = 0x01U,
    ENTITY_PLANT  = 0x02U,
    ENTITY_OTHER  = 0x03U
} entity_type_t;

#define Colour Color

typedef struct
{
    entity_type_t type;
    float food_units;
    bool dead;
    Vector3 position;
    string_t name;
    Colour colour;
    Vector3 size;
} pamats_t;

typedef struct
{
    entity_type_t type;
    pamats_t p;

    float energy;
    laiks_t age;
    float movement_efficiency;
    float food_efficiency;
} dziivnieks_t;

typedef struct
{
    entity_type_t type;
    pamats_t p;
} augs_t;

typedef struct
{
    entity_type_t type;
    pamats_t p;
} cits_t;

typedef union
{
    entity_type_t type;
    pamats_t p;

    dziivnieks_t animal;
    augs_t plant;
    cits_t other;
} buutne_t;


typedef enum
{
    DZIIVNIEKERR_VISSOK                 = 0x00U,
    DZIIVNIEKERR_GHENEREESHANAS_KLHUUME = 0x01U,
} dziivniekerr_t;

dziivniekerr_t Dziivnieks_Generate(int fermas_izmeers, int dziivnieku_skaits);
dziivniekerr_t Dziivnieks_Draw();
dziivniekerr_t Dziivnieks_CheckRay();

void Dziivnieks_Kusteeties(dziivnieks_t* d, Vector3 virziens);
void Dziivnieks_Eest(dziivnieks_t* d, buutne_t* eediens);
void Dziivnieks_Kliegt(dziivnieks_t* d); // citiem vārdiem, izdvest/radīt skaņu.




#endif
