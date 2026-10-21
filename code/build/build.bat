@echo off
setlocal enabledelayedexpansion
set "files=..\main.c"
for %%f in (..\src\*.c) do (
    set "files=!files! %%f"
)

gcc -o main.exe %files% C:\raylib\raylib\src\raylib.rc.data -s -static -O2 -std=c23 -Wall -Wextra -I..\inc -IC:\raylib\raylib\src -IC:\raylib\raylib\src\external -DPLATFORM_DESKTOP -LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm
REM gcc %files% -I..\inc -Wall -Wextra -std=gnu99 -o main
REM gcc -o core_basic_window.exe core_basic_window.c C:\raylib\raylib\src\raylib.rc.data -s -static -O2 -std=c99 -Wall -IC:\raylib\raylib\src -Iexternal -DPLATFORM_DESKTOP -lraylib -lopengl32 -lgdi32 -lwinmm

pause
