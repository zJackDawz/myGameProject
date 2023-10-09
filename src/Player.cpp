

#include "Player.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Player::Player(Vector2 pos, Texture spriteIdle, Texture spriteRun) {
    posX = pos.x;
    posY = pos.y;
    spriteWidth = (float)spriteIdle.width/6;
    spriteHeight = (float)spriteIdle.height;
    texture = spriteIdle;
    idle = spriteIdle;
    run = spriteRun;
    health = 20;
}

float Player::getPosX() {
    return posX;
}

float Player::getPosY() {
    return posY;
}

void Player::update(float deltaTime) {
    timeCount+=deltaTime;
    centerX = posX + spriteWidth/2;
    centerY = posY + spriteHeight/2;

    if (moving) {
        texture = run;
    }
    else {
        texture = idle;
    }

    if (skillActive) {
        Skill::skillUpdate(deltaTime, idle, Vector2{centerX,centerY}, 8, 8);
        if (millis - skillActiveTime > 2.8) {
            skillActive = false;
            speedBySkill = 0;
        }
    }

    Entity::update(deltaTime);

    if (state == 1) {
        implant();
    }

    Player::drawWeapon();

    if (attack) {
        drawAttack();
    }
    
}

void Player::input () {
    moving = false;
    if (attack) {
        playerspeed = 0.75 + speedBySkill/5;
    }
    else {
        playerspeed = 2.0 + speedBySkill;
    }

    if (GetMouseX() >  655 && attack != true) {
        Isleft = 1.0;
    }
    else if (GetMouseX() <  655 && attack != true){
        Isleft = -1.0;
    }

    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && posX < map.width-spriteWidth ) {
        posX += playerspeed;
        moving = true;
        }

    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && posX > 0) {
        posX -= playerspeed;
        moving = true;
        }

    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && posY > 0 ) {
        posY -= playerspeed;
        moving = true;
        }

    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && posY < map.height-spriteHeight) {
        posY += playerspeed;
        moving = true;
        }
    
    if (IsKeyPressed(KEY_F) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        state=1;
    }

    if (IsKeyPressed(KEY_Q) && millis - skillActiveTime > skillCooldown[0]) {
        skillActive = true;
        speedBySkill = 1.5;
        skillActiveTime = millis;
    }

    if ((IsMouseButtonDown(MOUSE_LEFT_BUTTON)) && millis - lastAttack > attackCooldown-speedBySkill*5) {
        attack = true;
        state = 0;
        lastAttack = millis;
        }
}

void Player::drawAttack() {
    // printf("%f\n", posX);
    float startHit = 8;
    float widthHitbox = 17;
    float heightHitbox = 22;
    float debugX{centerX+startHit};

    if (Isleft < 0) {
        debugX-=startHit*2+widthHitbox;
    }

    Rectangle slash = {debugX, centerY-(heightHitbox/2), widthHitbox, heightHitbox};
    DrawRectangleRec(slash, BLANK);
    Entity::attackFx(GetFrameTime(),8,tempFx, 0.20);
}

void Player::drawWeapon(){
    float scale = 0.5f;
    float hand = centerX;
    if (Isleft < 0) {
        hand-=scale*weaponWidth;
    }
    Rectangle source = (Rectangle){weaponWidth, 0.f, Isleft * weaponWidth, weaponHeight};
    Rectangle dest = (Rectangle){hand, posY, scale * weaponWidth, scale * weaponHeight};
    DrawTexturePro(weapon, source, dest, Vector2 {}, 0, WHITE);
}

Rectangle Player::hitboxAttack() {
    float debugX{centerX};
    if (Isleft < 0) {
        debugX-=25;
    }
    if (attack) 
        return Rectangle{debugX, centerY-(20/2), 25, 20};
    else
        return Rectangle{};
}

void Player::printStatus() {
    DrawText(TextFormat("Player Health : %d ", health), 10, 40, 20, DARKGRAY);
    DrawText(TextFormat("State : %d ", state), 10, 60, 20, DARKGRAY);
    DrawText(TextFormat("GreenPeaSeeds : %d ", seeds), 10, 80, 20, DARKGRAY);
    DrawText(TextFormat("Money : %d ", money), 10, 100, 20, DARKGRAY);
    if (skillCooldown[0]-(timeCount-skillActiveTime)>0) {
        DrawText(TextFormat("Skill Is On Cooldown Ma yed mae : %.2f ", skillCooldown[0]-(timeCount-skillActiveTime)), 10, 120, 60, RED);
    }
    else {
        DrawText("Skill Is Ready", 10, 120, 40, GREEN);
    }
    DrawText(TextFormat("Mouse  : %d ", GetMouseX()), 10, 160, 20, DARKGRAY);
}

void Player::get() {
    seeds++;
}

void Player::implant() {
    float startHit = 12;
    float debugX{centerX+startHit};

    if (Isleft < 0) {
        debugX-=startHit*2+(float)greenPea.width/4;
    }
    if (state == 1 ) {
    Rectangle plantHitbox = {debugX, spriteHeight+posY-((float)greenPea.height), (float)greenPea.width/4, (float)greenPea.height};
    DrawRectangleRec(plantHitbox, tintPlant);
    tintPlant =  {0, 228, 48, 240 };
    }
    if (IsMouseButtonUp(MOUSE_BUTTON_RIGHT) && seeds > 0 && state ==  1) {
        seeds--;
        state = 0;
        temp.x = debugX;
        temp.y = spriteHeight+posY-((float)greenPea.height);
        plant = true;
    }
    else if (IsMouseButtonUp(MOUSE_BUTTON_RIGHT) && state == 1) {
        state = 0;
        tintPlant = RED;
        Rectangle plantHitbox = {debugX, spriteHeight+posY-((float)greenPea.height), (float)greenPea.width/4, (float)greenPea.height};
        DrawRectangleRec(plantHitbox, tintPlant);
    }
    
}

Vector2 Player::plantHere() {
    return {temp.x, temp.y};
}

Rectangle Player::safeArea() {
    float margin = 100;
        return Rectangle{
                posX-margin/2,
                posY-margin/2,
                spriteWidth+margin,
                spriteHeight+margin};
}