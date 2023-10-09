#include "raylib.h"
#include "Entity.h"
#include <stdio.h>

Entity::Entity() {
}

void Entity::update(float deltaTime) {
        millis+=deltaTime;
        
        runningTime+=deltaTime;
        // printf("%f\n", millis);
        
        if (runningTime >= updateTime)
        {
                runningTime = 0.f;
                frame++;
                
                
                if (frame > maxFrames)
                frame = 0;
        }
        Rectangle source = (Rectangle){frame * spriteWidth, 0.f, Isleft * spriteWidth, spriteHeight};
        Rectangle dest = (Rectangle){posX, posY, spriteWidth, spriteHeight};
        DrawTexturePro(texture, source, dest, Vector2 {}, 0, colorSprite);
        if (millis - colorDelay > 0.1) { 
                colorSprite = WHITE;}
        
}

void Entity::attackFx(float deltaTime,int maxFrames, Texture tempfx, float scale) {
        Texture fx = tempfx;
        float fxWidth = (float)fx.width/maxFrames;
        float fxHeight = (float)fx.height;
        float hand = centerX - 15;
        
        tempTime+=deltaTime;
        
        if (tempTime >= 1.0f / 30.0f)
        {
                tempTime = 0.f;
                Fxframe++;
                
                if (Fxframe > maxFrames - 1){
                Fxframe = 0;
                attack = false;
                }
        }

        if (Isleft < 0 ) {
                hand-=fxWidth*scale - 30; 
        }

        if (attack) {
        Rectangle source = (Rectangle){Fxframe * fxWidth, 0.f, Isleft * fxWidth, fxHeight};
        Rectangle dest = (Rectangle){hand, centerY-fxHeight*scale/1.9f, scale * fxWidth, scale * fxHeight};
        DrawTexturePro(fx, source, dest, Vector2 {}, 0, WHITE);}
        
}



Rectangle Entity::hitbox() {
        return Rectangle{
                posX,
                posY,
                spriteWidth,
                spriteHeight};
}

void Entity::takeDamage(int damage) {
        health-= damage;
        colorSprite = RED;
        colorDelay = millis;
        if (health <= 0) {
                alive = false;
        }
}

// void Entity::undoMovement() {

// }

