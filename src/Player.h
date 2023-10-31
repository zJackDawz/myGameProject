
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "raylib.h"
#include "Item.h"
#include "Skill.h"
class Player : public Entity, public Item, public Skill {
public:
    Rectangle safeArea();

    Player() {}
    Player(Vector2 pos, Texture sprite, Texture spriteRun);
    virtual float getPosX();
    virtual float getPosY();
    virtual void update(float delTatime) override;
    virtual void input();

    void get();
    void implant();
    bool plant = false;

    virtual void drawAttack();
    void drawWeapon();
    void printStatus();

    Rectangle hitboxAttack();

    float playerspeed = 2.0;
    float attackCooldown  = 0.7;
    float lastAttack = -attackCooldown;

    Texture idle;
    Texture run;
    Texture weapon = LoadTexture("img/weapons/DAGGERS.png");
    Texture tempFx = LoadTexture("img/weapons/fx/slash.png");
    float weaponWidth = (float)weapon.width/15;
    float weaponHeight = (float)weapon.height/3;

    int state{};
    int seeds{};
    bool plantActive = false;
    Vector2 plantHere();
    Vector2 temp{};

    int money{};

    bool skillActive = false;
    float skillActiveTime{-20};
    float speedBySkill{};
    float skillCooldown[1] = {10};
    float timeCount{};

    Color tintPlant = { 0, 228, 48, 240 };

private:
    Vector2 pos{};
    Texture sprite{};
    Texture spriteRun{};

};

#endif