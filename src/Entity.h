#ifndef ENITY_H
#define ENITY_H

#include "raylib.h"
#include <stdio.h>
#include <time.h>

class Entity {
public:
        Entity();
        virtual ~Entity() {};
        Rectangle hitbox();
        void undoMovement();
        void takeDamage(int damage);
        bool alive{true};

        virtual void update(float deltaTime);

        float startTime = (float)time(NULL);
        int health{};
        float Isleft = 1.0f;
        float spriteWidth{};

protected:

        Texture2D map = LoadTexture("img/map/OpenWorldMap24x24.png");
        
        void attackFx(float deltaTime,int maxFrames, Texture tempfx, float scale);
        float millis{};
        
        float runningTime = 0;
        int frame{};
        int maxFrames{6};
        float updateTime{1.0f / 12.0f};
        
        float spriteHeight{};
        float posX{};
        float posY{};
        Texture texture;
        Color colorSprite = WHITE;
        float colorDelay{5};

        bool attack{false};

        bool moving = true;
        
        float centerX{};
        float centerY{};

        float tempTime{};
        int Fxframe{};

        
        int damage{};
};

#endif