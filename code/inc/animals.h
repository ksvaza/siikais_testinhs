#ifndef ANIMALS_H
#define ANIMALS_H


#include <stringutils.h>
#include <laiks.h>
#include <raylib.h>

#define Colour Color

typedef struct animal_base_privates_t animal_base_privates_t;
typedef struct animal_base_t
{
    animal_base_privates_t* private;

    void (*kusteeties)(struct animal_base_t* this, Vector3 direction);
    void (*eest)(struct animal_base_t* this);
    void (*skana)(struct animal_base_t* this);

    void (*select)(struct animal_base_t* this);
    void (*deselect)(struct animal_base_t* this);
    bool (*isSelected)(struct animal_base_t* this);

    void (*draw)(struct animal_base_t* this);
    void (*age)(struct animal_base_t* this, laiks_t currentTime);

    string_t (*getName)(struct animal_base_t* this);
    void (*setName)(struct animal_base_t* this, string_t newName);

    float (*getEnergy)(struct animal_base_t* this);
    void (*setEnergy)(struct animal_base_t* this, float newEnergy);

    laiks_t (*getAge)(struct animal_base_t* this);
    void (*setAge)(struct animal_base_t* this, laiks_t jaunaisVecums);
    
    Vector3 (*getPos)(struct animal_base_t* this);
    void (*setPos)(struct animal_base_t* this, Vector3 newpos);

    string_t (*getTypeName)(struct animal_base_t* this);
} animal_base_t;

typedef struct kraasains_dziivnieks_t
{
    animal_base_t base;
    Colour kraasa;
} kraasains_dziivnieks_t;

kraasains_dziivnieks_t* Animal_Kraasains_Create(string_t tname, Vector3 startpos, Colour kraasa);
void Animal_Kraasains_Destroy(kraasains_dziivnieks_t* this);

typedef struct gars_dziivnieks_t
{
    animal_base_t base;
    float garums;
} gars_dziivnieks_t;

gars_dziivnieks_t* Animal_Gars_Create(string_t tname, Vector3 startpos, float garums);
void Animal_Gars_Destroy(gars_dziivnieks_t* this);

#endif
