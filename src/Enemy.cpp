

#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

Enemy::Enemy(Texture spriteIdle, Texture spriteRun, int nType, Player *character) {
        target = character;
        posX = (float)(rand()%map.width);
        posY = (float)(rand()%map.height);
        spriteWidth = (float)spriteIdle.width/6;
        spriteHeight = (float)spriteIdle.height;
        texture = spriteIdle;
        type = nType;
        damage = 2;
        enemyspeed = 1.0f;
        defaultSpeed = enemyspeed;

        while (CheckCollisionRecs(hitbox(), target->safeArea()))
        {
                posX = (float)(rand()%map.width);
                posY = (float)(rand()%map.height);
        }
}

void Enemy::update(float deltaTime) {
        if (drop) {
                Item::drawItem(itemPos);
        }
        Entity::update(deltaTime);
}

void Enemy::SetTarget(Player *character)
{
    target = character;
}

void Enemy::enemyTrac(float targetPosX, float targetPosY) {

        if (target->Isleft > 0) {
                targetPosX-=target->spriteWidth-10;
        }
        else {
                targetPosX+=target->spriteWidth;
        }

        if((CheckCollisionRecs(hitbox(), target->hitbox()) && millis - lastHit > 0.25)){
                enemyspeed = defaultSpeed;
                enemyspeed*=-2.2;
                lastHit = millis;
                increaseSpeed = 0;
                target->takeDamage(damage);
        }

        if (millis - lastHit > 0.25) {
                enemyspeed = defaultSpeed + increaseSpeed;
        }

        if (type == 1){
                increaseSpeed+=0.001;
                // printf("%f\n", enemyspeed);
                if (targetPosX > posX) {posX+=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = 1.0f;}
                if (targetPosX < posX) {posX-=enemyspeed * -cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;}
                if (targetPosY > posY) {posY+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                if (targetPosY < posY) {posY-=enemyspeed * -sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}

        }

        if (type == 2){
        
                if (phase == 1) {
                //  move in X
                if (targetPosX > posX) {posX+=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = 1.0f;}
                if (targetPosX < posX) {posX-=enemyspeed * -cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;}

                // move out Y
                if (targetPosY > posY) {posY+=enemyspeed * -cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                if (targetPosY < posY) {posY-=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                }

                if ((abs(targetPosX - posX) < 20 ) || (abs(targetPosY - posY) < 200))
                {
                        phase = 2;
                }

                if (phase == 2) {
                //move out X
                if (targetPosX > posX) {posX+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = 1.0f;}
                if (targetPosX < posX) {posX-=enemyspeed * -sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;}
                
                //move in Y
                if (targetPosY > posY) {posY+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                if (targetPosY < posY) {posY-=enemyspeed * -sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                }

                if ((abs(targetPosY - posY) < 20) || (abs(targetPosX - posX) < 200)) {
                        phase = 3;
                }

                if (phase == 3) {
                //  move in X
                if (targetPosX > posX) {posX+=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = 1.0f;}
                if (targetPosX < posX) {posX-=enemyspeed * -cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;}
                
                //move in Y
                if (targetPosY > posY) {posY+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                if (targetPosY < posY) {posY-=enemyspeed * -sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
                }

                if ((abs(targetPosY - posY) > 200) || (abs(targetPosY - posY) < 200)) {
                        phase = 1;
                }
                // printf("%d\n", phase);
        }
}

void Enemy::dead(){
        Enemy::dropChance();
        enemyspeed = defaultSpeed;
        increaseSpeed = 0;
        // posX = (float)(rand()%map.width);
        // posY = (float)(rand()%map.height);
        posX = 9999;
        posY = 9999;
}

Vector2 Enemy::getPos() {
        return Vector2{posX,posY};
}

void Enemy::dropChance() {
        if (GetRandomValue(0,2) && drop != true) {
                drop = true;
                itemPos = {posX,posY};
        }
        else {
                alive = false;

        }
}

void Enemy::removeItem() {
        itemPos = {-1000,-1000};
        drop = false;
        alive = false;
}