#include "raylib.h"

#include "Screen.h"

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



int main(void) {

    // Set-up
    InitWindow(screenWidth, screenHeight, "SLEEPPEACH!");

    InitAudioDevice();

    SetTargetFPS(60);

    srand (time(NULL));

    Screen gameplay{};

    // Main Game LOOP
    
    while (gameRunning) {
        gameplay.startAction = false;
        gameplay.scoreAction = false;
        gameplay.submitAction = false;
        gameplay.startMenu();
        if (gameplay.exitAction) {
            break;
        }
        gameplay.Play();

        gameRunning = gameplay.End();
    }

    CloseAudioDevice();
    
    CloseWindow();

    return 0;
}

