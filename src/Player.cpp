#include "Player.h"

Player::Player(Vector2 pos, Texture sprite) {
    posX = pos.x;
    posY = pos.y;
    spriteWidth = (float)sprite.width/6;
    spriteHeight = (float)sprite.height;
    texture = sprite;
}

void Player::update(float deltaTime) {
    Entity::update(deltaTime);
}

