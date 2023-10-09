#include "raylib.h"
#include "Skill.h"

#include <stdio.h>

// Skill::Skill() {
// }

// Skill::~Skill() {
// }

void Skill::skillUpdate(float deltaTime, Texture skillFx, Vector2 pos, float skillMaxFrame,float skillMaxLine) {
        float skillWidth = (float)skill.width/skillMaxFrame;
        float skillHeight = (float)skill.height/skillMaxLine;
        runningTime+=deltaTime;

        
        if (runningTime >= updateTime)
        {
                runningTime = 0.f;
                frame++;
                
                if (frame > skillMaxFrame-1) {
                frame = 0;
                line++;
                }

                if(line == skillMaxLine-1 && frame == 5) {
                        line = 0;
                        frame = 0;
                }

        }

        // printf("frame %f : line %f\n",frame, line);
        Rectangle source = (Rectangle){frame * skillWidth, line * skillHeight, skillWidth, skillHeight};
        Rectangle dest = (Rectangle){pos.x-skillWidth/2+3, pos.y-skillHeight/2-2, skillWidth, skillHeight};
        DrawTexturePro(skill, source, dest, Vector2 {}, 0, WHITE);
}