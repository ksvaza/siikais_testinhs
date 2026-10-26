#ifndef CONTROLS_H
#define CONTROLS_H


#include <raylib.h>

void Controls_Update(float dt);

void Controls_Init();

Camera3D* Controls_GetCurrentCamera();
float Controls_GetCurrentTargetDistance();

Vector3 Controls_GetTarget();
void Controls_Move(Vector3 direction, bool sync);
void Controls_MoveTo(Vector3 position, bool sync);

bool Controls_Updated();

#endif
