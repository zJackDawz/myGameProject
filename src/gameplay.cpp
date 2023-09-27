#include "raylib.h"
#include "Enemy.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define screenWidth 1280
#define screenHeight 720

float playerspeed = 3.0;
bool playerMoving = false;
float IsLeft = 1.0f;
bool playerCanMove = true;
bool attack = false;
float myframetime = 0.01f;

void input (Vector2 *p) {
    Vector2 &target = *p;

    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) )) {
        target.x += playerspeed;
        playerMoving = true;
        IsLeft = 1.0f;
        }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        target.x -= playerspeed;
        playerMoving = true;
        IsLeft = -1.0f;
        }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        target.y -= playerspeed;
        playerMoving = true;
        }

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        target.y += playerspeed;
        playerMoving = true;
        }

    if (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        attack = true;
        }
}

int main(void)
{

    //---------------------------------------------------Setting----------------------------------------------------//
    //--------------------------------------------------------------------------------------------------------------//
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    srand (time(NULL));

    // Map
    Texture2D map = LoadTexture("img/map/OpenWorldMap24x24.png");
    Vector2 mapPos = {0,0};

    // Player
    Texture2D playerRun = LoadTexture("img/charactor/goblin_run_spritesheet.png");
    Texture2D playerIdle = LoadTexture("img/charactor/goblin_idle_spritesheet.png");
    Texture2D playerAnime = playerIdle;
    Vector2 playerDest = { (float)screenWidth/2, (float)screenHeight/2 };
    Rectangle playerFrameRec = { 0.0f, 0.0f, (float)playerAnime.width/6, (float)playerAnime.height };

    // Goblin
    Texture2D goblin = LoadTexture("img/charactor/goblin_run_spritesheet.png");
    Vector2 goblinPos = { 350.0f, 280.0f };
    Rectangle goblinFrameRec = { 0.0f, 0.0f, (float)goblin.width/6, (float)goblin.height };

    // Bush
    Texture2D bush = LoadTexture("img/map/Bush.png");
    Vector2 bushPos = { 450.0f, 280.0f };
    Rectangle bushRec = { 0.0f, 0.0f, (float)bush.width, (float)bush.height };

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    // Enemy enemy;

    int currentFrame = 0;
    int playerCurrentFrame = 0;
    int framesCounter = 0;
    int playerFramesCounter = 0;
    int framesSpeed = 8;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ playerDest.x + 20.0f, playerDest.y + 0.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 2.0f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------------------------------//

    // Main Game LOOP
    while (!WindowShouldClose())
    {

        framesCounter++;
        myframetime = myframetime + 0.01;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            // Pick Sprite
            goblinFrameRec.x = (float)currentFrame*(float)goblin.width/6;
        }

        playerFramesCounter++;
        if (playerFramesCounter >= (60/framesSpeed))
        {
            playerFramesCounter = 0;
            playerCurrentFrame++;

            if (playerCurrentFrame > 5) playerCurrentFrame = 0;

            // Pick Sprite
            playerFrameRec.x = (float)playerCurrentFrame*(float)playerIdle.width/6;
            
        }

        input(&playerDest);
        // enemy.enemyTrac(&goblinPos, &playerDest, &goblinFrameRec.width);

        if (playerMoving) {
            playerAnime = playerRun;
        }
        else {
            playerAnime = playerIdle;
        }

        camera.target = (Vector2){ playerDest.x + 0, playerDest.y + 0 };

        Vector2 slash = {45, 80};
        Vector2 hand = playerDest;
        hand.x = playerDest.x + ((float)playerAnime.width/6)/2;
        hand.y = playerDest.y + ((float)playerAnime.height)/2;

        Rectangle realslash = {hand.x, hand.y-slash.y/2, 45, 80};

        Rectangle hitboxEnemy = {goblinPos.x, goblinPos.y, (float)goblin.width/6, (float)goblin.height};

        if(IsLeft<1) {
            realslash.x -= slash.x;
        }

        Player player(playerDest, playerAnime);

        // Rectangle source = (Rectangle){playerFrameRec.x, 0.f, IsLeft * (float)playerAnime.width/6, (float)playerAnime.height};
        // Rectangle dest = (Rectangle){playerDest.x, playerDest.y, (float)playerIdle.width/6, (float)playerIdle.height};

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);
                DrawTextureEx(map, mapPos, 0.0, 1.0f, WHITE);

                if (attack) {
                    DrawRectangleRec(realslash, Color{255,255,255,255});

                    // if (CheckCollisionPointRec(goblinPos, realslash)) {
                    //     goblinPos = { 350.0f, 280.0f };
                    // }
                    if (CheckCollisionRecs(hitboxEnemy, realslash)) {
                        goblinPos = { (float)(rand()%map.width) , (float)(rand()%map.height) };
                    }
                }

                DrawCircleV(ballPosition, 20, MAROON);
                DrawTextureRec(bush, bushRec, bushPos, WHITE);
                DrawTextureRec(goblin, goblinFrameRec, goblinPos, WHITE);
                // DrawTextureRec(playerAnime, playerFrameRec, playerDest, WHITE);
                // DrawTexturePro(playerAnime, source, dest, Vector2 {}, 0, WHITE);
                player.update(myframetime);
                // void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint)
                

            EndMode2D();

            DrawText("move with arrow keys", 10, 10, 20, DARKGRAY);

        EndDrawing();

        // printf("%f\n",(float)GetFrameTime());

        playerMoving = false;
        attack = false;

    }

    UnloadTexture(goblin);
    UnloadTexture(playerIdle);
    UnloadTexture(playerRun);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}