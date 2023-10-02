

#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

Enemy::Enemy(Vector2 pos, Texture spriteIdle, Texture spriteRun, int nType) { 
        posX = pos.x;
        posY = pos.y;
        spriteWidth = (float)spriteIdle.width/6;
        spriteHeight = (float)spriteIdle.height;
        texture = spriteIdle;
        type = nType;
        damage = 2;
        enemyspeed = 1.0f;
        defaultSpeed = enemyspeed;
}

void Enemy::update(float deltaTime) {
        Entity::update(deltaTime);
}

void Enemy::SetTarget(Player *character)
{
    target = character;
}

void Enemy::enemyTrac(float targetPosX, float targetPosY) {

        if((CheckCollisionRecs(hitbox(), target->hitbox()) && millis - lastHit > 20)){
                enemyspeed*=-2;
                lastHit = millis;
                target->takeDamage(damage);
        }

        if (enemyspeed < 0 && millis - lastHit > 20) {
                enemyspeed = defaultSpeed;
        }

        if (type == 1){

        if (targetPosX > posX) {posX+=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;Isleft = 1.0f;}
        if (targetPosX < posX) {posX-=enemyspeed * -cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;}
        if (targetPosY > posY) {posY+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
        if (targetPosY < posY) {posY-=enemyspeed * -sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}

        }

        if (type == 2){
        
        

        if (phase == 1) {
        //  move in X
        if (targetPosX > posX) {posX+=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;Isleft = 1.0f;}
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
        if (targetPosX > posX) {posX+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;Isleft = 1.0f;}
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
        if (targetPosX > posX) {posX+=enemyspeed * cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;Isleft = 1.0f;}
        if (targetPosX < posX) {posX-=enemyspeed * -cos(Vector2Angle({posX, posY},{targetPosX,targetPosY}));Isleft = -1.0f;}

        
        //move in Y
        if (targetPosY > posY) {posY+=enemyspeed * sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
        if (targetPosY < posY) {posY-=enemyspeed * -sin(Vector2Angle({posX, posY},{targetPosX,targetPosY}));}
        }

        if ((abs(targetPosY - posY) < 20) || (abs(targetPosY - posY) < 200)) {
                phase = 1;
        }
        // printf("%d\n", phase);
        }


}

void Enemy::dead(){
       posX = (float)(rand()%map.width);
       posY = (float)(rand()%map.height);
}

void Enemy::getMap(Texture mapp){
        map = mapp;
}

Vector2 Enemy::getPos() {
        return Vector2{posX,posY};
}