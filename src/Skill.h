#ifndef SKILL_H
#define SKILL_H

class Skill {
public:
        Skill() {}
        ~Skill() {}
protected:
        void skillUpdate(float deltaTime, Texture skillFx, Vector2 pos, float skillMaxFrame,float skillMaxLine);
        Texture skill = {LoadTexture("img/charactor/sunburn_spritesheet.png")};
        
        float runningTime{};
        float frame{};
        float line{};
        float updateTime{1.0f/12.0f};
};

#endif