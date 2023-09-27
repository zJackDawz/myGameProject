#include "raylib.h"
class Entity {
public:
        Entity();
        void hitbox();
        void undoMovement();
        void takeDamage();
        virtual void update(float deltaTime);
        int check = 1;
protected:
        float Isleft = 1.0f;
        float runningTime{};
        int frame{};
        int maxFrames{6};
        float updateTime{1.0f / 12.0f};
        float spriteWidth{};
        float spriteHeight{};
        float posX{};
        float posY{};
        Texture texture;
};