#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#include <stringutils.h>
#include <laiks.h>
#include <soundtrackhandler.h>
#include <controls.h>
//#include <dziivnieki.h>
#include <dziivnieku_ferma.h>
#include <soundeffects.h>

int main(void)
{
    string_t na = String_NewC("Jauns "), me = String_NewC("logs"), name = String_Empty();
    String_AddS(&name, na, me);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, name.c_str);

    InitAudioDevice();

    printf("Sveika, pasaule!\n");

    printf("\nIzveidots logs %s\n\n", name.c_str);
    Soundtracks_Load("../res/minecraft/");
    Soundtracks_GenerateRandomQueue();
    Soundtracks_Start(0);
    SetMasterVolume(0.5f);
    //while(1);

    // if (Dziivnieks_Generate(8, 24) != DZIIVNIEKERR_VISSOK)
    // {
    //     printf("Nav ok\n");
    //     while(1);
    // }

    Ferma_Generate(8, 50);



    // Wave swerr_wave = LoadWave("../res/rebuild error.wav");
    // Sound swerr = LoadSoundFromWave(swerr_wave);
    // UnloadWave(swerr_wave);

    seff_error_t sefferror = SoundEffect_InitLibrary(8);
    if (SoundEffect_IsError(sefferror))
    {
        printf("\nError: %d\n\n", sefferror);
        while(1);
    }

    sefferror = SoundEffect_LoadWave("../res/rebuild error.wav", String_TempC("klhuume"));
    if (SoundEffect_IsError(sefferror))
    {
        printf("\nError: %d\n\n", sefferror);
        while(1);
    }

    sefferror = SoundEffect_LoadWave("../res/interference detection complete.wav", String_TempC("interference"));
    if (SoundEffect_IsError(sefferror))
    {
        printf("\nError: %d\n\n", sefferror);
        while(1);
    }

    Image ikona = LoadImage("../res/logo_ikona.png");
    ImageFormat(&ikona, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(ikona);

    int windowWidth = GetRenderWidth(), windowHeight = GetRenderHeight();

    SetExitKey(KEY_NULL);

    Vector2 playaPos = {(float)windowWidth / 2.0f, (float)windowHeight / 2.0f};
    // Camera2D kamera = (Camera2D){};
    // kamera.target = (Vector2){playaPos.x + 20.0f, playaPos.y + 20.0f};
    // kamera.offset = (Vector2){(float)windowWidth / 2.0f, (float)windowHeight / 2.0f};
    // kamera.rotation = 0.0f;
    // kamera.zoom = 1.0f;

    Controls_Init();

    

    

    string_t liednamebase = String_Empty();
    string_t liedname = String_Empty();
    string_t liedlange = String_NewL(16);

    Soundtracks_TogglePause();

    laiks_t currentTime = (laiks_t){};
    float deltaTime = 0.0f;
    while(!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        currentTime = Laiks_Seconds((float)GetTime());
        //printf("Laiks %f\n", Laiks_InSeconds(currentTime));

        if (IsWindowResized())
        {
            windowWidth = GetScreenWidth();
            windowHeight = GetScreenHeight();
            //kamera.offset = (Vector2){(float)windowWidth / 2.0f, (float)windowHeight / 2.0f};
        }

        if (IsKeyPressed(KEY_ESCAPE) || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)))
        {
            sefferror = SoundEffect_PlaySound(String_TempC("klhuume"));
            if (SoundEffect_IsError(sefferror))
            {
                printf("\nError: %d\n\n", sefferror);
                while(1);
            }
        }

        if (IsKeyPressed(KEY_P) || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_SPACE)))
        {
            Soundtracks_TogglePause();
            SoundEffect_PlaySound(String_TempC("interference"));
        }

        if (Soundtracks_Update(currentTime))
        {
            String_Fill(liedname, 0);
            String_Fill(liedlange, 0);
            String_AddS(&liedname, liednamebase, Soundtracks_GetCurrentTrack().name);
            sprintf_s(liedlange.c_str, liedlange.length, "%3.0f/%3.0f", Soundtracks_GetCurrentPlaytime(), Soundtracks_GetCurrentLength());
        }

        Controls_Update(deltaTime);

        static bool cammoving = false;
        static bool camfresh = false;
        static laiks_t camtime = {};
        if (cammoving && Ferma_GetFocus())
        {
            static Vector3 dir = {};
            if (camfresh)
            {
                // te nav
                animal_base_t* d = Ferma_GetFocus();
                dir = Vector3Add(d->getPos(d), Vector3Invert(Controls_GetTarget()));
                camfresh = false;
            }
            Controls_Move(Vector3Scale(dir, deltaTime), true);

            if (Laiks_InSeconds(Laiks_Subtract(currentTime, camtime)) >= 1.0f)
            {
                animal_base_t* d = Ferma_GetFocus();
                cammoving = false;
                //Controls_MoveTo(dz->getPos(dz), true);
            }
        }

        Ferma_Update(currentTime);
        animal_base_t* dz = Ferma_CheckRay(GetScreenToWorldRay(GetMousePosition(), *Controls_GetCurrentCamera()));
        

        BeginDrawing();

            ClearBackground(SKYBLUE);

            BeginMode3D(*Controls_GetCurrentCamera());
                // DrawRectangle(0, (int)((float)windowHeight * 0.8f), windowWidth, (int)((float)windowHeight * 0.2f), GREEN);
                // DrawCircle((int)playaPos.x, (int)playaPos.y, 20, DARKGREEN);
                // DrawCube((Vector3){}, 1.0f, 1.0f, 1.0f, GREEN);
                // DrawCube((Vector3){0.0f, 0.75f, 0.0f}, 0.5f, 0.5f, 0.5f, RAYWHITE);
                //DrawGrid(10, 1.0f);

                Ferma_Draw();
            EndMode3D();

            // ui

            DrawRectangle(0, 0, windowWidth, 60, BLACK);
            float prozent = Soundtracks_GetCurrentPlaytime() / Soundtracks_GetCurrentLength();
            DrawRectangle(20, 6, (int)((float)(windowWidth - 40) * prozent), 10, RAYWHITE);
            DrawRectangle(20 + (int)((float)(windowWidth - 40) * prozent), 8, (int)((float)(windowWidth - 40) * (1.0f - prozent)), 10, DARKGRAY);
        
            DrawText(liedname.c_str, 10, 30, 20, RAYWHITE);
            DrawText(liedlange.c_str, (windowWidth - MeasureText(liedlange.c_str, 20)) / 2, 30, 20, RAYWHITE);
            
            string_t playaPosText = String_NewL(256);
            animal_base_t* d = Ferma_GetFocus();
            if (d) sprintf_s(playaPosText.c_str, playaPosText.length, "Target position:\n x=%f\n y=%f\n z=%f\n targetdist=%f\n\nDzpos:\n x=%f\n y=%f\nz=%f", Controls_GetCurrentCamera()->target.x, Controls_GetCurrentCamera()->target.y, Controls_GetCurrentCamera()->target.z, Controls_GetCurrentTargetDistance(), d->getPos(d).x, d->getPos(d).y, d->getPos(d).z);
            else sprintf_s(playaPosText.c_str, playaPosText.length, "Target position:\n x=%f\n y=%f\n z=%f\n targetdist=%f", Controls_GetCurrentCamera()->target.x, Controls_GetCurrentCamera()->target.y, Controls_GetCurrentCamera()->target.z, Controls_GetCurrentTargetDistance());
            DrawText(playaPosText.c_str, 10, 70, 20, BLACK);

            if (dz)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    Ferma_SetFocus(dz);
                    cammoving = true;
                    camfresh = true;
                    camtime = currentTime;
                } 
                Vector3 dzpos = dz->getPos(dz);
                Vector2 texpos = {};
                string_t dname = dz->getName(dz);
                string_t dtype = dz->getTypeName(dz);
                Colour col = ORANGE;
                if (dtype.c_str)
                {
                    if (String_Compare(dtype, String_TempC("garais")))
                    {
                        texpos = GetWorldToScreen(Vector3Add(dzpos, (Vector3){ 0.0f, ((gars_dziivnieks_t*)dz)->garums, 0.0f }), *Controls_GetCurrentCamera());
                    }
                    else if (String_Compare(dtype, String_TempC("kraasainais")))
                    {
                        col = ((kraasains_dziivnieks_t*)dz)->kraasa;
                        texpos = GetWorldToScreen(Vector3Add(dzpos, (Vector3){ 0.0f, 1.6f, 0.0f }), *Controls_GetCurrentCamera());
                    }
                }
                if (dname.c_str) DrawText(dname.c_str, (int)(texpos.x - (float)MeasureText(dname.c_str, 20) / 2.0f), texpos.y - 22, 20, BLACK);
                if (dtype.c_str) DrawText(dtype.c_str, (int)(texpos.x - (float)MeasureText(dtype.c_str, 20) / 2.0f), texpos.y - 44, 20, BLACK);
            }

        EndDrawing();
    }


    CloseAudioDevice();


    String_Terminate(name);
}
 