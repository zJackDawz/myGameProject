#include "raylib.h"

#include "Enemy.h"
#include "Player.h"
#include "Plant.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>

#define screenWidth 1280
#define screenHeight 720

float mainCount{};

int screen{};

int score{};

bool gameRunning = true;

bool init = true;

void gameplay();

int main(void) {
    // Set-up
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    srand (time(NULL));

    // Main Game LOOP
    while (gameRunning) {

        if (screen == 0) {
            gameplay();
        }

        // End Screen
        while (screen == 1) {
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("You Suck!", (screenWidth-100)/8, (screenHeight-200)/2, 200, RED);
                DrawText(TextFormat("Money : %d ", score), (screenWidth-200)/2, (screenHeight-40)/2+100, 40, DARKGRAY);
            EndDrawing();
            if (IsKeyPressed(KEY_R)) {
                screen = 0;
            }
            else if (WindowShouldClose()) {
                gameRunning = false;
                screen = 99;
            }
        }

    }

    // UnloadTexture(goblin);
    // UnloadTexture(playerIdle);
    // UnloadTexture(playerRun);
    // UnloadTexture(map);

    CloseWindow();

    return 0;
}

void gameplay() {

    // ---------------------- Map ---------------------- //
    Texture2D map = LoadTexture("img/map/OpenWorldMap24x24.png");
    Vector2 mapPos = {0,0};


    // ---------------------- Player ---------------------- //
    Texture2D playerRun = LoadTexture("img/charactor/goblin_run_spritesheet.png");
    Texture2D playerIdle = LoadTexture("img/charactor/goblin_idle_spritesheet.png");
    Vector2 playerPos = { (float)screenWidth/2, (float)screenHeight/2 };


    // ---------------------- Goblin ---------------------- //
    Texture2D goblin = LoadTexture("img/charactor/knight_run_spritesheet.png");

    // ---------------------- Plants ---------------------- //
    std::vector<Plant> plants;

    // ---------------------- Bush ---------------------- //
    Texture2D bush = LoadTexture("img/map/Bush.png");
    Vector2 bushPos = { 450.0f, 280.0f };
    Rectangle bushRec = { 0.0f, 0.0f, (float)bush.width, (float)bush.height };

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };


    // ---------------------- Class init ---------------------- //
    
    Enemy enemy1{playerRun, goblin, 1};
    Enemy enemy2{goblin, goblin, 2};
    // Enemy *enemies[] { &enemy1, &enemy2};
    std::vector<Enemy> enemies;
    std::vector<Item> items;

    for (int i = 0; i < 1; ++i) {
        if (GetRandomValue(1,1)){
            Enemy enemy(goblin, goblin, 2);
            enemies.push_back(enemy);
            }
        else {
            Enemy enemy(playerRun, goblin, 1);
            enemies.push_back(enemy);
            }
    }

    Player player{playerPos, playerIdle, playerRun};
    
    for (auto &enemy : enemies)
    {
        enemy.SetTarget(&player);
    }

    // ---------------------- Camera ---------------------- //
    Camera2D camera = { 0 };
    camera.target = (Vector2){ playerPos.x + 20.0f, playerPos.y + 0.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    while (player.alive && !IsKeyPressed(KEY_P)) {
            mainCount+=GetFrameTime();

            player.input();

            for (auto &enemy : enemies)
            {
                enemy.enemyTrac(player.getPosX(), player.getPosY());
            }

            camera.target = (Vector2){ player.getPosX() + 0, player.getPosY() + 0 };

            BeginDrawing();

                ClearBackground(RAYWHITE);
                
                BeginMode2D(camera);
                    DrawTextureEx(map, mapPos, 0.0, 1.0f, WHITE);

                    // if (mainCount > 10) {
                    //     mainCount = 0;
                    //     if (GetRandomValue(0,4)){
                    //         Enemy enemy(goblin, goblin, 2);
                    //         enemies.push_back(enemy);
                    //         }
                    //     else {
                    //         Enemy enemy(playerRun, goblin, 1);
                    //         enemies.push_back(enemy);
                    //         }
                    // }

                    for (auto &enemy : enemies)
                    {
                        if (CheckCollisionRecs(enemy.hitbox(), player.hitboxAttack())) {
                            enemy.dead();
                        }
                        if (CheckCollisionRecs(enemy.itemHitbox(), player.hitbox())) {
                            player.get();
                            enemy.removeItem();
                        }
                        enemy.SetTarget(&player);
                    }

                    for (auto &plant : plants) {
                        if (CheckCollisionRecs(player.hitbox(),plant.hitbox()) && plant.readyToHarvest && player.state == 0) {
                            plant.tint = GOLD;
                            if (IsKeyPressed(KEY_SPACE)) {
                                player.money += plant.remove();
                            }
                        }
                        else {
                            plant.tint = WHITE;
                        }
                    }

                    DrawCircleV(ballPosition, 20, MAROON);
                    DrawTextureRec(bush, bushRec, bushPos, WHITE);

                    for (auto &plant : plants)
                    {
                        plant.drawPlant(GetFrameTime());
                    }
                    
                    player.update(GetFrameTime());

                    if (player.plant) {
                        Plant plant{player.plantHere()};
                        plants.push_back(plant);
                        player.plant = false;
                    }

                    for (auto &enemy : enemies)
                    {
                        enemy.update(GetFrameTime());
                    }
                    
                EndMode2D();

                DrawText("move with arrow keys || w a s d", 10, 10, 20, DARKGRAY);
                player.printStatus();

                
            EndDrawing();
    }
    screen = 1;
    score = player.money;
    UnloadTexture(goblin);
    UnloadTexture(playerIdle);
    UnloadTexture(playerRun);
    UnloadTexture(map);
}

void intitClear() {
    
}