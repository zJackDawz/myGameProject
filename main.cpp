#include "raylib.h"

#define screenWidth 1280
#define screenHeight 720

float playerspeed = 3.0;
bool playerMoving = false;
bool playerLeft = false;

void input ( Vector2 *p) {
    Vector2 &target = *p;
    if (IsKeyDown(KEY_RIGHT)) {
        target.x += playerspeed;
        playerMoving = true;
        playerLeft = false;
        }

    if (IsKeyDown(KEY_LEFT)) {
        target.x -= playerspeed;
        playerMoving = true;
        playerLeft = true;
        }

    if (IsKeyDown(KEY_UP)) {
        target.y -= playerspeed;
        playerMoving = true;
        }

    if (IsKeyDown(KEY_DOWN)) {
        target.y += playerspeed;
        playerMoving = true;
        }
}

int main(void)
{

    //---------------------------------------------------Setting----------------------------------------------------//
    //--------------------------------------------------------------------------------------------------------------//
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Player
    Texture2D playerRun = LoadTexture("img/charactor/goblin_run_spritesheet.png");
    Texture2D playerIdle = LoadTexture("img/charactor/goblin_idle_spritesheet.png");
    Texture2D playerAnime = playerIdle;
    Vector2 playerDest = { (float)screenWidth/2, (float)screenHeight/2 };
    Rectangle playerFrameRec = { 0.0f, 0.0f, (float)playerAnime.width/6, (float)playerAnime.height };

    // Goblin
    Texture2D goblin = LoadTexture("img/charactor/goblin_run_spritesheet.png");
    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)goblin.width/6, (float)goblin.height };

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    int currentFrame = 0;
    int framesCounter = 0;
    int playerFramesCounter = 0;
    int framesSpeed = 8;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ playerDest.x + 20.0f, playerDest.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 2.0f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------------------------------//

    // Main Game LOOP
    while (!WindowShouldClose())
    {

        framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            // Pick Sprite
            frameRec.x = (float)currentFrame*(float)goblin.width/6;
        }

        playerFramesCounter++;
        if (playerFramesCounter >= (60/framesSpeed))
        {
            playerFramesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            // Pick Sprite
            playerFrameRec.x = (float)currentFrame*(float)playerIdle.width/6;
            
        }

        input(&playerDest);

        if (playerMoving == true) {
            playerAnime = playerRun;
        }
        else {
            playerAnime = playerIdle;
        }
        if (playerLeft == true && playerFrameRec.width > 0) {
            playerFrameRec.width = -playerFrameRec.width;
        }
        if (playerLeft == false && playerFrameRec.width < 0) {
            playerFrameRec.width = -playerFrameRec.width;
        }


        camera.target = (Vector2){ playerDest.x + 20, playerDest.y + 20 };

        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                DrawCircleV(ballPosition, 20, MAROON);
                DrawTextureRec(goblin, frameRec, position, WHITE);
                DrawTextureRec(playerAnime, playerFrameRec, playerDest, WHITE);

            EndMode2D();

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

        EndDrawing();

        playerMoving = false;

    }

    UnloadTexture(goblin);

    CloseWindow();

    return 0;
}