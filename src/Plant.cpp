#include "raylib.h"
#include "Plant.h"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

Plant::Plant(Vector2 getpos) : getpos(getpos)  {
        pos = getpos;
}

void Plant::drawPlant(float deltaTime) {
        growthTime+=deltaTime;
        // printf("%f : %f\n", growthTime, perGrowth);
        if (growthTime >= perGrowth)
        {
                growthTime = 0.f;
                period++;
                
                if (period == maxGrowth){
                        period = maxGrowth - 1;
                        readyToHarvest = true;
                }
        }
        Rectangle source = (Rectangle){period * (float)greenPea.width/4, 0.f, (float)greenPea.width/4, (float)greenPea.height};
        Rectangle dest = (Rectangle){pos.x, pos.y, (float)greenPea.width/4, (float)greenPea.height};
        DrawTexturePro(greenPea,source, dest, Vector2{}, 0, tint);
}

Rectangle Plant::hitbox() {
        return Rectangle{pos.x, pos.y, (float)greenPea.width/4, (float)greenPea.height};
}

int Plant::remove() {
        UnloadTexture(greenPea);
        pos = {-1000, -1000};
        return 20;
}