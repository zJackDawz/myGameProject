#include "raylib.h"
#include "Entity.h"

Entity::Entity() {
}

void Entity::update(float deltaTime) {
        runningTime += deltaTime;
        if (runningTime >= updateTime)
        {
                runningTime = 0.f;
                frame++;
                
                if (frame > maxFrames)
                frame = 0;
        }
        Rectangle source = (Rectangle){frame * spriteWidth, 0.f, Isleft * spriteWidth, spriteHeight};
        Rectangle dest = (Rectangle){posX, posY, spriteWidth, spriteHeight};
        DrawTexturePro(texture, source, dest, Vector2 {}, 0, WHITE);

}

// void Entity::hitbox() {
//         // return Rectangle{
//                 // getScreenPos().x,
//                 // getScre      enPos().y,
//                 // width * scale,
//                 // height * scale
// }


// void Entity::undoMovement() {

// }

// void Entity::takeDamage() {

// }