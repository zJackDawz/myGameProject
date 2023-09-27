
#include "Entity.h"
#include "raylib.h"
class Player : public Entity {
public:
    Player(Vector2 pos, Texture sprite);
    virtual void update(float delTatime) override;
};