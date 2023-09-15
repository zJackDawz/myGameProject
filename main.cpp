#include "raylib.h"

#define weightScreen 1280
#define heighScreen 720

int centerX(int x){
    int centerX = (weightScreen - x - 1) / 2;
    return centerX;
}

int centerY(int y){
    int centerX = (heighScreen - y - 1) / 2;
    return centerX;
}

int main(void)
{
    InitWindow(weightScreen, heighScreen, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", centerX(420), centerY(0), 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}