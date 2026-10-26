#ifndef DZIIVNIEKU_FERMA_H
#define DZIIVNIEKU_FERMA_H


#include <raylib.h>

#include <animals.h>
#include <laiks.h>

void Ferma_Generate(int fermas_izmeers, int dziivnieku_skaits);
void Ferma_Update(laiks_t currentTime);
void Ferma_Draw();

void Ferma_SetFocus(animal_base_t* dz);
animal_base_t* Ferma_GetFocus();
animal_base_t* Ferma_CheckRay(Ray ray);


#endif
