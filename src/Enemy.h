#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "raylib.h"
#include "Player.h"
#include "Item.h"


class Enemy : public Entity, public Item {
public:
    Enemy(Vector2 pos, Texture sprite, Texture spriteRun, int nType);
    float enemyspeed{};
    void enemyTrac(float targetPosX, float targetPosY);
    virtual void update(float delTatime) override;
    void dead();
    void getMap(Texture mapp);
    void SetTarget(Player *character);
    Texture map{};
    Vector2 getPos();

    int type{};
    int phase = 1;
    float defaultSpeed{};
private:
    Player* target;
    int lastHit{};
};


#endif