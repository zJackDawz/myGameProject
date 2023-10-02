#include "raylib.h"

#include "Enemy.h"
#include "Player.h"
#include "Item.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define screenWidth 1280
#define screenHeight 720

int main(void)
{

    //---------------------------------------------------Setting----------------------------------------------------//
    //--------------------------------------------------------------------------------------------------------------//
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    srand (time(NULL));

    // ---------------------- Map ---------------------- //
    Texture2D map = LoadTexture("img/map/OpenWorldMap24x24.png");
    Vector2 mapPos = {0,0};


    // ---------------------- Player ---------------------- //
    Texture2D playerRun = LoadTexture("img/charactor/goblin_run_spritesheet.png");
    Texture2D playerIdle = LoadTexture("img/charactor/goblin_idle_spritesheet.png");
    Vector2 playerPos = { (float)screenWidth/2, (float)screenHeight/2 };


    // ---------------------- Goblin ---------------------- //
    Texture2D goblin = LoadTexture("img/charactor/knight_run_spritesheet.png");
    Vector2 goblinPos = { 350.0f, 280.0f };

    // ---------------------- item ---------------------- //
    Item seed{};


    // ---------------------- Bush ---------------------- //
    Texture2D bush = LoadTexture("img/map/Bush.png");
    Vector2 bushPos = { 450.0f, 280.0f };
    Rectangle bushRec = { 0.0f, 0.0f, (float)bush.width, (float)bush.height };

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };


    // ---------------------- Class init ---------------------- //
    Enemy enemy1{goblinPos, playerRun, goblin, 1};
    Enemy enemy2{goblinPos, goblin, goblin, 2};
    Enemy *enemies[] { &enemy1, &enemy2};
    for (auto enemy : enemies)
    {
        enemy->getMap(map);
    }
    


    Player player{playerPos, playerIdle, playerRun};
    
    for (auto enemy : enemies)
    {
        enemy->SetTarget(&player);
    }


    // ---------------------- Camera ---------------------- //
    Camera2D camera = { 0 };
    camera.target = (Vector2){ playerPos.x + 20.0f, playerPos.y + 0.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------------------------------//

    // Main Game LOOP
    while (!WindowShouldClose())
    {

        player.input();
        for (auto enemy : enemies)
        {
            enemy->enemyTrac(player.getPosX(), player.getPosY());
        }

        camera.target = (Vector2){ player.getPosX() + 0, player.getPosY() + 0 };

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);
                DrawTextureEx(map, mapPos, 0.0, 1.0f, WHITE);


                for (auto enemy : enemies)
                {
                    if (CheckCollisionRecs(enemy->hitbox(), player.hitboxAttack())) {
                    seed.chance(enemy->getPos());
                    enemy->dead();
                    }
                }

                if (CheckCollisionRecs(seed.itemHitbox(), player.hitbox())) {
                    player.get();
                    seed.get();
                }


                DrawCircleV(ballPosition, 20, MAROON);
                DrawTextureRec(bush, bushRec, bushPos, WHITE);

                if (player.plantActive) {
                    seed.drawPlant(player.plantHere());
                }

                seed.drawItem();
                
                player.update(GetFrameTime());

                for (auto enemy : enemies)
                {
                    enemy->update(GetFrameTime());
                }
                

            EndMode2D();

            DrawText("move with arrow keys || w a s d", 10, 10, 20, DARKGRAY);
            player.printStatus();

        EndDrawing();

    }

    UnloadTexture(goblin);
    UnloadTexture(playerIdle);
    UnloadTexture(playerRun);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}