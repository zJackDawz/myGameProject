#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "raylib.h"
#include "Player.h"
#include "Item.h"


class Enemy : public Entity, public Item {
public:
    Enemy(Texture sprite, Texture spriteRun, int nType);
    float enemyspeed{};
    void enemyTrac(float targetPosX, float targetPosY);
    virtual void update(float delTatime) override;
    void dead();
    void SetTarget(Player *character);
    Vector2 getPos();

    int type{};
    int phase = 1;
    float defaultSpeed{};
    void dropChance();
    void removeItem();
    float increaseSpeed{};
private:
    Player* target;
    float lastHit{};
};


#endif