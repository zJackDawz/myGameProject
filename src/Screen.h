#ifndef SCREEN_H
#define SCREEN_H

#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "Plant.h"

#include <stdio.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream> 
#include <algorithm> 

class Screen : public Player, public Enemy, public Plant
{
private:
        int screen{};
        float mainCount{};
        
        
public:
        Screen();
        ~Screen() {}

        Texture2D map{};
        Vector2 mapPos{};
        Texture2D playerRun{};
        Texture2D playerIdle{};
        Texture2D playerRun2{};
        Texture2D playerIdle2{};
        Vector2 playerPos{};
        Texture2D goblin{};
        Vector2 ballPosition{};

        
        void startMenu();
        void Play();
        bool End();

        // std::string playerName{};
        // int score{};
        struct Score {
            std::string playerName;
            int score;
        };

        std::vector<Score> scores;

        void AddScore(const Score& newScore);
        void SaveScoresToFile();
        void SortScores();
        void LoadScoresFromFile();

        void drawTutorial();

        int coin{};
        char userName[12];
        char name[12 + 1] = "\0";

        int startState = 0;
        bool startAction = false;
	int scoreState = 0;
	bool scoreAction = false;
        int exitState = 0;
        bool exitAction = false;
	int submitState = 0;
	bool submitAction = false;
        int backState = 0;
	bool backAction = false;

        float lastReleased = -4;

        float timeCount{};

        bool inputName = false;

        Music backgroundMusic = LoadMusicStream("sound/background-music.mp3");
        float timePlayed = 0.0f;

        float enemySpawn{};
        
};

#endif