#ifndef CONTROLS_H
#define CONTROLS_H


#include <raylib.h>

void Controls_Update(float dt);

void Controls_Init();

Camera3D* Controls_GetCurrentCamera();


#endif
