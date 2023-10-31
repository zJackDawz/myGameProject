#include "raylib.h"
#include "Screen.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#define screenWidth 1280
#define screenHeight 720

struct Score {
            std::string playerName;
            int score;
};
std::vector<Score> scores;

Screen::Screen() {
        // --------------- Init Texture ---------------
        // ---------------------- Map ---------------------- //
        map = LoadTexture("img/map/OpenWorldMap24x24.png");
        mapPos = {0,0};


        // ---------------------- Player ---------------------- //
        playerRun = LoadTexture("img/charactor/goblin_run_spritesheet.png");
        playerIdle = LoadTexture("img/charactor/goblin_idle_spritesheet.png");
        playerPos = { (float)screenWidth/2, (float)screenHeight/2 };


        // ---------------------- Goblin ---------------------- //
        goblin = LoadTexture("img/charactor/knight_run_spritesheet.png");

        // ---------------------- Ball ---------------------- //
        
        ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
}

void Screen::startMenu() {

    PlayMusicStream(backgroundMusic);
    

    std::vector<Score> scoreboard;

	Texture2D background_6 = LoadTexture("img/menuBackground/sky.png");
	Texture2D background_5 = LoadTexture("img/menuBackground/far-clouds.png");
	Texture2D background_4 = LoadTexture("img/menuBackground/near-clouds.png");
	Texture2D background_3 = LoadTexture("img/menuBackground/far-mountains.png");
    Texture2D background_2 = LoadTexture("img/menuBackground/mountains.png");
    Texture2D background_1 = LoadTexture("img/menuBackground/trees.png");

    Texture2D gameName = LoadTexture("img/menuBackground/game-name.png");
    Texture2D creatorName = LoadTexture("img/menuBackground/creator-name.png");

	float scrolling_6 = 0.0f;
    float scrolling_5 = 0.0f;
    float scrolling_4 = 0.0f;
    float scrolling_3 = 0.0f;
    float scrolling_2 = 0.0f;
    float scrolling_1 = 0.0f;

	float scale = 3.0f;

	int numFramese = 3;

    name[0] = '\0';

	Texture2D start = LoadTexture("img/button/start.png");
	Texture2D scoreboard2D = LoadTexture("img/button/scoreboard.png");
    Texture2D exit = LoadTexture("img/button/exit.png");
    Texture2D submit = LoadTexture("img/button/submit.png");
    Texture2D back = LoadTexture("img/button/back.png");

	// Define frame rectangle for drawing
    float frameHeight = (float)start.height/numFramese;
    Rectangle startSource = { 0, 0, (float)start.width, frameHeight };
	Rectangle scoreSource = { 0, 0, (float)scoreboard2D.width, frameHeight };
    Rectangle exitSource = { 0, 0, (float)exit.width, frameHeight };
    Rectangle submitSource = { 0, 0, (float)submit.width, frameHeight };
    Rectangle backSource = { 0, 0, (float)back.width, frameHeight };

    // Define button bounds on screen
    Rectangle btnBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f - start.height/numFramese/2.0f, (float)start.width, frameHeight };

	Rectangle scoreboardBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese/2.0f, (float)start.width, frameHeight };

    Rectangle exitBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese*1.5f, (float)start.width, frameHeight };

    Rectangle submitBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese/2.0f, (float)start.width, frameHeight };

    Rectangle backBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese*1.5f, (float)start.width, frameHeight };

    

    Vector2 mousePoint = { 0.0f, 0.0f };

    float fontsize = 80;

    int MAX_INPUT_CHARS = 12;

    // name{};
    int letterCount = 0;

    Rectangle textBox = { screenWidth/2.0f - ((float)fontsize*(float)8.7)/2.0f, 290, (float)fontsize*(float)8.7, fontsize+10 };

    int framesCounter = 0;

    LoadScoresFromFile();

    // Main game loop
    while (!submitAction && !exitAction)
    {
        UpdateMusicStream(backgroundMusic);
        timePlayed = GetMusicTimePlayed(backgroundMusic)/GetMusicTimeLength(backgroundMusic);
        if (timePlayed > 1.0f) timePlayed = 1.0f;
        exitAction = false;
        // Update
        //----------------------------------------------------------------------------------
		scrolling_6 -= 0.1f;
        scrolling_5 -= 0.25f;
        scrolling_4 -= 0.5f;
        scrolling_3 -= 0.75f;
        scrolling_2 -= 1.25f;
        scrolling_1 -= 2.0f;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
		if (scrolling_6 <= -background_6.width*scale) scrolling_6 = 0;
        if (scrolling_5 <= -background_5.width*scale) scrolling_5 = 0;
        if (scrolling_4 <= -background_4.width*scale) scrolling_4 = 0;
        if (scrolling_3 <= -background_3.width*scale) scrolling_3 = 0;
        if (scrolling_2 <= -background_2.width*scale) scrolling_2 = 0;
        if (scrolling_1 <= -background_1.width*scale) scrolling_1 = 0;
        //----------------------------------------------------------------------------------

		mousePoint = GetMousePosition();

        // Check start state
        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) startState = 2;
            else startState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) startAction = true;
        }
        else startState = 0;

		startSource.y = startState*frameHeight;

        // Check scoreboard state
		if (CheckCollisionPointRec(mousePoint, scoreboardBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) scoreState = 2;
            else scoreState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) scoreAction = true;
        }
        else scoreState = 0;

		scoreSource.y = scoreState*frameHeight;

        // Check exit state
        if (CheckCollisionPointRec(mousePoint, exitBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) exitState = 2;
            else exitState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) exitAction = true;
        }
        else exitState = 0;

		exitSource.y = exitState*frameHeight;

        // Check submit state
        if (CheckCollisionPointRec(mousePoint, submitBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) submitState = 2;
            else submitState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && (name[0] != '\0')) submitAction = true;
            else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && (name[0] == '\0')) {
                lastReleased = timeCount;
                inputName = false;
            }
        }
        else submitState = 0;

        submitSource.y = submitState*frameHeight;


        // Check back state
        if (CheckCollisionPointRec(mousePoint, backBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) backState = 2;
            else backState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) backAction = true;

        }
        else backState = 0;

		backSource.y = backState*frameHeight;

        if (startAction) {
            scoreboardBounds = { };
            exitBounds = { };
            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                    inputName = true;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
            framesCounter++;
        }
        else if (scoreAction) {
            exitBounds = { };
        }

        if (backAction) {
            startAction = false;
            scoreAction = false;
            backAction = false;
            name[0] = '\0';
            letterCount = 0;
        }

        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

			DrawTextureEx(background_6, (Vector2){ scrolling_6, 0 }, 0.0f, scale*1.2f, WHITE);
            DrawTextureEx(background_6, (Vector2){ background_6.width*scale*1.2f + scrolling_6, 0 }, 0.0f, scale*1.2f, WHITE);

			DrawTextureEx(background_5, (Vector2){ scrolling_5, 0 }, 0.0f, scale, WHITE);
            DrawTextureEx(background_5, (Vector2){ background_5.width*scale + scrolling_5, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_5, (Vector2){ background_5.width*scale*2 + scrolling_5, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_5, (Vector2){ background_5.width*scale*3 + scrolling_5, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_5, (Vector2){ background_5.width*scale*4 + scrolling_5, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_5, (Vector2){ background_5.width*scale*5 + scrolling_5, 0 }, 0.0f, scale, WHITE);

			DrawTextureEx(background_4, (Vector2){ scrolling_4, 0 }, 0.0f, scale, WHITE);
            DrawTextureEx(background_4, (Vector2){ background_4.width*scale + scrolling_4, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_4, (Vector2){ background_4.width*scale*2 + scrolling_4, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_4, (Vector2){ background_4.width*scale*3 + scrolling_4, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_4, (Vector2){ background_4.width*scale*4 + scrolling_4, 0 }, 0.0f, scale, WHITE);

            DrawTextureEx(background_3, (Vector2){ scrolling_3, 0 }, 0.0f, scale, WHITE);
            DrawTextureEx(background_3, (Vector2){ background_3.width*scale + scrolling_3, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_3, (Vector2){ background_3.width*scale*2 + scrolling_3, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_3, (Vector2){ background_3.width*scale*3 + scrolling_3, 0 }, 0.0f, scale, WHITE);

            DrawTextureEx(background_2, (Vector2){ scrolling_2, 0 }, 0.0f, scale, WHITE);
            DrawTextureEx(background_2, (Vector2){ background_2.width*scale + scrolling_2, 0 }, 0.0f, scale, WHITE);
			DrawTextureEx(background_2, (Vector2){ background_2.width*scale*2 + scrolling_2, 0 }, 0.0f, scale, WHITE);

            if (!startAction && !scoreAction) {


                submitBounds = {};

                DrawTextureRec(start, startSource, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);

                DrawTextureEx(background_1, (Vector2){ scrolling_1, 50 }, 0.0f, scale, WHITE);
                DrawTextureEx(background_1, (Vector2){ background_1.width*scale + scrolling_1, 50 }, 0.0f, scale, WHITE);
                DrawTextureEx(background_1, (Vector2){ background_1.width*scale*2 + scrolling_1, 50 }, 0.0f, scale, WHITE);

                scoreboardBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese/2.0f, (float)start.width, frameHeight };
                DrawTextureRec(scoreboard2D, scoreSource, (Vector2){ scoreboardBounds.x, scoreboardBounds.y }, WHITE);

                exitBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese*1.5f, (float)start.width, frameHeight };
                DrawTextureRec(exit, exitSource, (Vector2){ exitBounds.x, exitBounds.y }, WHITE);

                DrawTextureV(gameName, Vector2 {}, WHITE); 
                DrawTextureV(creatorName, Vector2 {}, WHITE); 
                drawTutorial();
            }
            else if (startAction)
            {
                DrawTextureEx(background_1, (Vector2){ scrolling_1, 50 }, 0.0f, scale, WHITE);
                DrawTextureEx(background_1, (Vector2){ background_1.width*scale + scrolling_1, 50 }, 0.0f, scale, WHITE);
                DrawTextureEx(background_1, (Vector2){ background_1.width*scale*2 + scrolling_1, 50 }, 0.0f, scale, WHITE);

                DrawRectangleRec(textBox, LIGHTGRAY);
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);

                DrawText(name, (int)textBox.x + 15, (int)textBox.y + 4, fontsize, MAROON);

                DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 265, 20, RAYWHITE);

                submitBounds = { screenWidth/2.0f - start.width/2.0f, screenHeight/2.0f + start.height/numFramese/2.0f, (float)start.width, frameHeight };
                DrawTextureRec(submit, submitSource, (Vector2){ submitBounds.x, submitBounds.y }, WHITE);

                DrawTextureRec(back, backSource, (Vector2){ backBounds.x, backBounds.y }, WHITE);


                if (letterCount < MAX_INPUT_CHARS)
                {
                    if (timeCount - lastReleased < 3 && !inputName) DrawText("Please Enter Your Name", screenWidth/2.0f - (50*5), 318, 40, RED);
                    else if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 22 + MeasureText(name, fontsize), (int)textBox.y + 8, fontsize, MAROON);
                    
                }

                else DrawText("Press BACKSPACE to delete chars...", screenWidth/2.0f - MeasureText("Press BACKSPACE to delete chars...", 20)/2, 385, 20, GRAY); 

            }
            else if (scoreAction) {
                DrawTextureEx(background_1, (Vector2){ scrolling_1, 50 }, 0.0f, scale, WHITE);
                DrawTextureEx(background_1, (Vector2){ background_1.width*scale + scrolling_1, 50 }, 0.0f, scale, WHITE);
                DrawTextureEx(background_1, (Vector2){ background_1.width*scale*2 + scrolling_1, 50 }, 0.0f, scale, WHITE);
                // Render the scoreboard
                DrawText("Scoreboard", 10, 10, 20, WHITE); // Title
                // Render each score
                for (size_t i = 0; i < scores.size() && i < 5; i++) {
                    std::string scoreText = scores[i].playerName + ": " + std::to_string(scores[i].score);
                    DrawText(scoreText.c_str(), 10, 40 + i * 30, 16, WHITE);
                }

                DrawTextureRec(back, backSource, (Vector2){ backBounds.x, backBounds.y }, WHITE);

            }
            
        

        EndDrawing();
        timeCount+=GetFrameTime();
        //----------------------------------------------------------------------------------
    }

    submitAction = false;
    startAction = false;

	UnloadTexture(background_6);
    UnloadTexture(background_5);
    UnloadTexture(background_4);
    UnloadTexture(background_3);
    UnloadTexture(background_2);
    UnloadTexture(background_1);

	UnloadTexture(scoreboard2D);
	UnloadTexture(start);
}



void Screen::Play() {

        std::vector<Score> scoreboard;
        
        // ---------------------- Class init ---------------------- //
    
        Player player{playerPos, playerIdle, playerRun};

        std::vector<Enemy> enemies;
        std::vector<Item> items;
        std::vector<Plant> plants;

        for (int i = 0; i < 5; ++i) {
                if (GetRandomValue(0,4)){
                // Enemy *enemy3 = new Enemy{playerRun, goblin, 1};
                Enemy *enemy = new Enemy(goblin, goblin, 2, &player);
                enemies.push_back(*enemy);
                }
                else {
                Enemy *enemy = new Enemy(playerRun, goblin, 1, &player);
                enemies.push_back(*enemy);
                }
        }

        // ---------------------- Camera ---------------------- //

        Camera2D camera = { 0 };
        camera.target = (Vector2){ playerPos.x + 20.0f, playerPos.y + 0.0f };
        camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
        camera.zoom = 2.0f;

        
        // ---------------------- Game-core ---------------------- //
        while (player.alive && !WindowShouldClose()) {
            UpdateMusicStream(backgroundMusic);
            PlayMusicStream(backgroundMusic);
            timePlayed = GetMusicTimePlayed(backgroundMusic)/GetMusicTimeLength(backgroundMusic);
            if (timePlayed > 1.0f) timePlayed = 1.0f;
                mainCount+=GetFrameTime();

                player.input();

                for (auto &enemy : enemies) {
                        enemy.enemyTrac(player.getPosX(), player.getPosY());
                }

                if (mainCount > 1) {
                        mainCount = 0;
                        if (GetRandomValue(0,6) == 2) {
							Enemy *enemy = new Enemy(goblin, goblin, 2, &player);
							enemies.push_back(*enemy);
							printf("knight spawn");
                        }
                        else {
							Enemy *enemy = new Enemy(playerRun, goblin, 1, &player);
							enemies.push_back(*enemy);
                        }
                }

                camera.target = (Vector2){ player.getPosX() + 0, player.getPosY() + 0 };

                BeginDrawing();

                        ClearBackground(RAYWHITE);
                        
                        BeginMode2D(camera);
                        DrawTextureEx(map, mapPos, 0.0, 1.0f, WHITE);

                        

                        for (auto enemy = enemies.begin(); enemy != enemies.end(); ) {
                                // enemy->SetTarget(&player);
                                
                                if (CheckCollisionRecs(enemy->hitbox(), player.hitboxAttack())) {
                               		enemy->dead();
                                }
                                
                                if (CheckCollisionRecs(enemy->itemHitbox(), player.hitbox())) {
									player.get();
									enemy->removeItem();
                                }
                                
                                if (!enemy->alive) {
                                	enemy = enemies.erase(enemy);
                                } else {
                                	++enemy;
                                }
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

                        for (auto &plant : plants) {
                                plant.drawPlant(GetFrameTime());
                        }

                        player.update(GetFrameTime());

                        if (player.plant) {
                                Plant plant{player.plantHere()};
                                plants.push_back(plant);
                                player.plant = false;
                        }

                        for (auto &enemy : enemies) {
                                enemy.update(GetFrameTime());
                        }
                        
                        EndMode2D();

                        DrawText("move with arrow keys || w a s d", 10, 10, 20, DARKGRAY);
                        player.printStatus();

                        
                EndDrawing();
        }
        screen = 1;
        coin = player.money;    
        Score newScore;
        newScore.playerName = name;
        newScore.score = coin;
        AddScore(newScore);
        SaveScoresToFile();
        startAction = false;
        scoreAction = false;
        scores.clear();
}

bool Screen::End() {
        while (screen == 1) {
            UpdateMusicStream(backgroundMusic);
            timePlayed = GetMusicTimePlayed(backgroundMusic)/GetMusicTimeLength(backgroundMusic);
            if (timePlayed > 1.0f) timePlayed = 1.0f;
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("You Lose!", (screenWidth-100)/8, (screenHeight-200)/2, 200, RED);
                DrawText(TextFormat("Money : %d ", coin), (screenWidth-200)/2, (screenHeight-40)/2+100, 40, DARKGRAY);
                DrawText("Press R to back to Menu or ESC to exit the Game", 10, 10, 20, GRAY);
            EndDrawing();
            if (IsKeyDown(KEY_R)) {
                screen = 0;
                return true;
            }
            else if (WindowShouldClose()) {
                screen = 0;
				UnloadTexture(goblin);
				UnloadTexture(playerIdle);
				UnloadTexture(playerRun);
				UnloadTexture(map);

                UnloadMusicStream(backgroundMusic);
                return false;
            }
        }
        return true;
}

void Screen::LoadScoresFromFile() {
    std::ifstream file("scores.txt");
    if (file.is_open()) {
        Score score;
        while (file >> score.playerName >> score.score) {
            scores.push_back(score);
        }
        file.close();
    }
}

void Screen::SortScores() {
    std::sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) {
        return a.score > b.score;
    });
}

void Screen::SaveScoresToFile() {
    std::ofstream file("scores.txt");
    if (file.is_open()) {
        for (const Score& score : scores) {
            file << score.playerName << " " << score.score << std::endl;
        }
        file.close();
    }
}

void Screen::AddScore(const Score& newScore) {
    scores.push_back(newScore);
    Screen::SortScores();
}

void Screen::drawTutorial() {
    DrawText("Press WASD to Move", 10, 635, 15, GRAY);
    DrawText("Press Q to use Skill", 10, 655, 15, GRAY);
    DrawText("Press LeftMouseClick to use Attack", 10, 675, 15, GRAY);
    DrawText("Press RightMouseClick to use Plant", 10, 695, 15, GRAY);
}