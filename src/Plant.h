#ifndef PLANT_H
#define PLANT_H

#include "raylib.h"

class Plant {
public:
        Plant() {}

        Plant(Vector2 getpos);
        void drawPlant(float deltaTime);

        Vector2 pos{};
        Texture greenPea = LoadTexture("img/plants/green_pea.png");

        float growthTime{};
        float perGrowth{1.0};
        float period{};
        float maxGrowth{4};

        Color tint = WHITE;

        bool readyToHarvest{false};

        Rectangle hitbox();
        int remove();
private:
        Vector2 getpos;
};

#endif