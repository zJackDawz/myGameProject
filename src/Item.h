#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"

class Item {
public:
        Item();
        ~Item();
        void drawItem(Vector2 pos);
        void drawPlant(Vector2 pos);
        Rectangle itemHitbox();
protected:
        bool drop{};        
        Texture greenPea = LoadTexture("img/plants/green_pea.png");
        Texture greenPeaSeeds = LoadTexture("img/plants/green_pea_seeds.png");
        Vector2 itemPos{};
        float itemWidth{};
        float itemHeight{};
};

#endif