#pragma once

#include "Utils/Vector2D.h"
#include "Transform.h"

class Projectile : public Component
{
public:
    Projectile();
    Projectile(int mrange, int mspeed, Vector2D vector, Entity mEntity);
    ~Projectile();
    bool isActive() { return active; }
    void update();

private:
    Transform *transform;
    Vector2D velocity;
    Entity entity;
    int range;
    int speed;
    int distance;
    bool active = true;
};