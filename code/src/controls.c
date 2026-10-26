#include "controls.h"
#include "rcamera.h"
#include "raymath.h"

Camera3D controlsCamera = {};

bool controlsFlippedArrowMovement = false;
bool controlsUpdated = false;

float controlsMouseTranslationSpeed = 0.0008f;
float controlsMouseRotationSpeed = 0.01f;
float controlsMouseScrollSpeed = 0.2f;
float controlsMouseZoomSpeed = 0.2f;
float controlsMouseAltSpeed = 0.2f;

void Controls_Update(float dt) // cietdarbi
{
    Vector2 mouse = GetMouseDelta();
    float zoom = Vector3Distance(controlsCamera.position, controlsCamera.target);

    Vector2 wheel = GetMouseWheelMoveV();

    if (wheel.y != 0.0f)
    {
        CameraMoveToTarget(&controlsCamera, zoom * controlsMouseScrollSpeed * wheel.y);
        controlsUpdated = true;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
    {
        //EnableCursor();
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE))
    {
        //EnableCursor();
    }

    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            CameraMoveRight(&controlsCamera, -controlsMouseTranslationSpeed * zoom * mouse.x, false);
            CameraMoveUp(&controlsCamera, controlsMouseTranslationSpeed * zoom * mouse.y);
            controlsUpdated = true;
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            CameraMoveRight(&controlsCamera, -0.1 * zoom * (controlsFlippedArrowMovement ? -1.0f : 1.0f), false);
            controlsUpdated = true;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            CameraMoveRight(&controlsCamera, 0.1 * zoom * (controlsFlippedArrowMovement ? -1.0f : 1.0f), false);
            controlsUpdated = true;
        }
        if (IsKeyPressed(KEY_UP))
        {
            CameraMoveUp(&controlsCamera, 0.1 * zoom * (controlsFlippedArrowMovement ? -1.0f : 1.0f));
            controlsUpdated = true;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            CameraMoveUp(&controlsCamera, -0.1 * zoom * (controlsFlippedArrowMovement ? -1.0f : 1.0f));
            controlsUpdated = true;
        }
    }
    else
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            CameraYaw(&controlsCamera, -controlsMouseRotationSpeed * mouse.x, true);
            CameraPitch(&controlsCamera, -controlsMouseRotationSpeed * mouse.y, true, true, true);
        }
        
        if (IsKeyPressed(KEY_LEFT))
        {
            CameraYaw(&controlsCamera, -15 * DEG2RAD * (controlsFlippedArrowMovement ? -1.0f : 1.0f), true);
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            CameraYaw(&controlsCamera, 15 * DEG2RAD * (controlsFlippedArrowMovement ? -1.0f : 1.0f), true);
        }
        if (IsKeyPressed(KEY_UP))
        {
            CameraPitch(&controlsCamera, -15 * DEG2RAD * (controlsFlippedArrowMovement ? -1.0f : 1.0f), true, true, true);
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            CameraPitch(&controlsCamera, 15.0f * PI / 180.0f * (controlsFlippedArrowMovement ? -1.0f : 1.0f), true, true, true);
        }
    }

    // UpdateCamera(&controlsCamera, CAMERA_FREE);
}

void Controls_Init()
{
    controlsCamera.position = (Vector3){ 0.0f, 0.0f, 10.0f };
    controlsCamera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    controlsCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    controlsCamera.fovy = 80.0f * (1080.0f / 1920.0f);
    controlsCamera.projection = CAMERA_PERSPECTIVE;
}

Camera3D* Controls_GetCurrentCamera()
{
    return &controlsCamera;
}

float Controls_GetCurrentTargetDistance()
{
    return Vector3Distance(controlsCamera.position, controlsCamera.target);
}

Vector3 Controls_GetTarget()
{
    return controlsCamera.target;
}
void Controls_Move(Vector3 direction, bool sync)
{
    controlsCamera.target = Vector3Add(controlsCamera.target, direction);
    if (sync) controlsCamera.position = Vector3Add(controlsCamera.position, direction);
}
void Controls_MoveTo(Vector3 position, bool sync)
{
    Vector3 d = Vector3Add(position, Vector3Invert(controlsCamera.target));
    controlsCamera.target = Vector3Add(controlsCamera.target, d);
    if (sync) controlsCamera.position = Vector3Add(controlsCamera.position, d);
}


bool Controls_Updated()
{
    return controlsUpdated;
}
