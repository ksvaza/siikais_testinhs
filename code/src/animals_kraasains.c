#include "animals.h"

#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <raymath.h>

#include <stringutils.h>
#include <laiks.h>
#include <soundeffects.h>

#ifndef ANIMAL_BASE_PRIVATES_T_
#define ANIMAL_BASE_PRIVATES_T_
typedef struct animal_base_privates_t
{
    string_t nosaukums;
    float energija;
    laiks_t nulle;
    laiks_t vecums;

    float move_eff;
    float eat_eff;

    Vector3 position;

    bool selected;

    string_t typename;
} animal_base_privates_t;
#endif

// --------------------------------------------------------------------------------------------------------------------------------

// kraasains dziivnieks
// --------------------------------------------------------------------------------------------------------------------------------

void _Animal_Kraasains_Kusteeties(animal_base_t* this, Vector3 direction)
{
    if (!this || !this->private) return;

    this->private->position = Vector3Add(this->private->position, direction);
}
void _Animal_Kraasains_Eest(animal_base_t* this)
{
    if (!this || !this->private) return;

    // palicis
}
void _Animal_Kraasains_Skana(animal_base_t* this)
{
    if (!this || !this->private) return;

    SoundEffect_PlaySound(String_TempC("kraasainais"));
}

void _Animal_Kraasains_Select(animal_base_t* this)
{
    if (!this || !this->private) return;

    this->private->selected = true;
}
void _Animal_Kraasains_Deselect(animal_base_t* this)
{
    if (!this || !this->private) return;

    this->private->selected = false;
}
bool _Animal_Kraasains_IsSelected(animal_base_t* this)
{
    if (!this || !this->private) return false;

    return this->private->selected;
}

RayCollision _Animal_Kraasains_CheckRay(animal_base_t* this, Ray ray)
{
    if (!this || !this->private) return (RayCollision){};

    Matrix m = MatrixTranslate(this->private->position.x, this->private->position.y, this->private->position.z);
    return GetRayCollisionMesh(ray, GenMeshCylinder(0.4f, 1.6f, 8), m);
}

void _Animal_Kraasains_Draw(animal_base_t* this)
{
    if (!this || !this->private) return;

    DrawCapsule
    (
        Vector3Add(this->private->position, (Vector3){ 0.0f, 0.4f, 0.0f }),
        Vector3Add(this->private->position, (Vector3){ 0.0f, 1.2f, 0.0f }),
        0.4f,
        16, 4,
        ((kraasains_dziivnieks_t*)this)->kraasa
    );

    if (_Animal_Kraasains_IsSelected(this)) DrawCapsuleWires
    (
        Vector3Add(this->private->position, (Vector3){ 0.0f, 0.4f, 0.0f }),
        Vector3Add(this->private->position, (Vector3){ 0.0f, 1.2f, 0.0f }),
        0.5f,
        8, 4,
        GREEN
    );
}
void _Animal_Kraasains_Age(animal_base_t* this, laiks_t currentTime)
{
    if (!this || !this->private) return;

    if (Laiks_InSeconds(this->private->nulle) <= 0.0f)
    {
        this->private->nulle = currentTime;
    }
    else if (Laiks_InSeconds(this->private->nulle) + Laiks_InSeconds(this->private->vecums) < Laiks_InSeconds(currentTime))
    {
        this->private->vecums = Laiks_Subtract(currentTime, this->private->nulle);
    }
}

string_t _Animal_Kraasains_GetName(animal_base_t* this)
{
    if (!this || !this->private) return String_Empty();

    return this->private->nosaukums;
}
void _Animal_Kraasains_SetName(animal_base_t* this, string_t newName)
{
    if (!this || !this->private) return;

    String_Terminate(this->private->nosaukums);
    this->private->nosaukums = String_NewS(newName);
    if (newName.temp) String_Terminate(newName);
}

float _Animal_Kraasains_GetEnergy(animal_base_t* this)
{
    if (!this || !this->private) return -1.0f;

    return this->private->energija;
}
void _Animal_Kraasains_SetEnergy(animal_base_t* this, float newEnergy)
{
    if (!this || !this->private) return;

    this->private->energija = newEnergy;
}

laiks_t _Animal_Kraasains_GetAge(animal_base_t* this)
{
    if (!this || !this->private) return Laiks_Seconds(0.0f);

    return this->private->vecums;
}
void _Animal_Kraasains_SetAge(animal_base_t* this, laiks_t jaunaisVecums)
{
    if (!this || !this->private) return;

    laiks_t d = Laiks_Subtract(jaunaisVecums, this->private->vecums);
    this->private->nulle = Laiks_Subtract(this->private->nulle, d);
    this->private->vecums = jaunaisVecums;
}

Vector3 _Animal_Kraasains_GetPos(animal_base_t* this)
{
    if (!this || !this->private) return (Vector3){};

    return this->private->position;
}
void _Animal_Kraasains_SetPos(animal_base_t* this, Vector3 newpos)
{
    if (!this || !this->private) return;

    _Animal_Kraasains_Kusteeties(this, Vector3Add(newpos, Vector3Negate(this->private->position)));
}

string_t _Animal_Kraasains_GetTypeName(animal_base_t* this)
{
    if (!this || !this->private) return String_Empty();

    return this->private->typename;
}

// ----------------------------------------------------------------



// ----------------------------------------------------------------

kraasains_dziivnieks_t* Animal_Kraasains_Create(string_t tname, Vector3 startpos, Colour kraasa)
{
    kraasains_dziivnieks_t* this = (kraasains_dziivnieks_t*)malloc(sizeof(kraasains_dziivnieks_t));
    if (!this) return nullptr;
    memset(this, 0, sizeof(kraasains_dziivnieks_t));
    
    this->base.private = (animal_base_privates_t*)malloc(sizeof(animal_base_privates_t));
    if (!this->base.private)
    {
        free(this);
        return nullptr;
    }
    memset(this->base.private, 0, sizeof(animal_base_privates_t));

    this->base.private->nosaukums = String_NewS(tname);
    this->base.private->energija = 1.0f;
    this->base.private->nulle = Laiks_Seconds(0.0f);
    this->base.private->vecums = Laiks_Seconds(0.0f);
    this->base.private->move_eff = 1.0f;
    this->base.private->eat_eff = 1.0f;
    this->base.private->position = startpos;
    this->base.private->selected = false;
    this->base.private->typename = String_NewC("kraasainais");

    this->base.kusteeties = _Animal_Kraasains_Kusteeties;
    this->base.eest = _Animal_Kraasains_Eest;
    this->base.skana = _Animal_Kraasains_Skana;

    this->base.select = _Animal_Kraasains_Select;
    this->base.deselect = _Animal_Kraasains_Deselect;
    this->base.isSelected = _Animal_Kraasains_IsSelected;

    this->base.checkRay = _Animal_Kraasains_CheckRay;

    this->base.draw = _Animal_Kraasains_Draw;
    this->base.age = _Animal_Kraasains_Age;

    this->base.getName = _Animal_Kraasains_GetName;
    this->base.setName = _Animal_Kraasains_SetName;

    this->base.getEnergy = _Animal_Kraasains_GetEnergy;
    this->base.setEnergy = _Animal_Kraasains_SetEnergy;

    this->base.getAge = _Animal_Kraasains_GetAge;
    this->base.setAge = _Animal_Kraasains_SetAge;

    this->base.getPos = _Animal_Kraasains_GetPos;
    this->base.setPos = _Animal_Kraasains_SetPos;

    this->base.getTypeName = _Animal_Kraasains_GetTypeName;

    this->kraasa = kraasa;

    if (tname.temp) String_Terminate(tname);

    return this;
}
void Animal_Kraasains_Destroy(kraasains_dziivnieks_t* this)
{
    if (!this) return;

    String_Terminate(this->base.private->nosaukums);
    String_Terminate(this->base.private->typename);

    if (this->base.private) free(this->base.private);
    free(this);
}

// --------------------------------------------------------------------------------------------------------------------------------
