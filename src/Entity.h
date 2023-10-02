#ifndef ENITY_H
#define ENITY_H

#include "raylib.h"

class Entity {
public:
        Entity();
        Rectangle hitbox();
        void undoMovement();
        void takeDamage(int damage);

        virtual void update(float deltaTime);
        

protected:
        
        void attackFx(float deltaTime,int maxFrames, Texture tempfx, float scale);
        float millis{};
        float Isleft = 1.0f;
        float runningTime = 0;
        int frame{};
        int maxFrames{6};
        float updateTime{1.0f / 12.0f};
        float spriteWidth{};
        float spriteHeight{};
        float posX{};
        float posY{};
        Texture texture;
        Color colorSprite = WHITE;
        float colorDelay{};

        bool attack{false};

        bool moving = true;
        
        float centerX{};
        float centerY{};

        float tempTime{};
        int Fxframe{};

        int health{};
        int damage{};
};

#endif