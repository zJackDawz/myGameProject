// #include "raylib.h"

// #define screenWidth 1280
// #define screenHeight 720

// int centerX(int x){
//     int centerX = (screenWidth - x - 1) / 2;
//     return centerX;
// }

// int centerY(int y){
//     int centerX = (screenHeight - y - 1) / 2;
//     return centerX;
// }

// int main(void)
// {
//     // Setting
//     InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

//     Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

//     SetTargetFPS(60);

//     // Main Game LOOP
//     while (!WindowShouldClose())
//     {
//         if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
//         if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
//         if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
//         if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        
//         BeginDrawing();

//             ClearBackground(RAYWHITE);

//             DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

//             DrawCircleV(ballPosition, 50, MAROON);

//         EndDrawing();
//     }

//     CloseWindow();

//     return 0;
// }