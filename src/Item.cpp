#include "raylib.h"
#include "raymath.h"
#include "Item.h"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

Item::Item() {
        itemWidth = greenPeaSeeds.width;
        itemHeight = greenPeaSeeds.height;
}

Item::~Item() {
}

void Item::drawItem(Vector2 pos) {
        Rectangle source = (Rectangle){0.f, 0.f, itemWidth, itemHeight};
        Rectangle dest = (Rectangle){pos.x, pos.y, itemWidth, itemHeight};
        DrawTexturePro(greenPeaSeeds, source, dest, Vector2 {}, 0, WHITE);
}

Rectangle Item::itemHitbox() {
        return Rectangle {itemPos.x,itemPos.y,itemWidth,itemHeight};
}

void Item::drawPlant(Vector2 pos) {
        Rectangle source = (Rectangle){0.f, 0.f, (float)greenPea.width/4, (float)greenPea.height};
        Rectangle dest = (Rectangle){pos.x, pos.y, (float)greenPea.width/4, (float)greenPea.height};
        DrawTexturePro(greenPea,source, dest, Vector2{}, 0, WHITE);
}

