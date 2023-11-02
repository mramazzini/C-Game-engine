#pragma once
#include "Vector2D.h"
#include <set>
#include "ECS/Core/Core.h"
#include <iomanip>

class Transform : public Component
{

public:
    Vector2D pos;
    std::set<Entity> *colliders;
    Vector2D velocity;

    Vector2D acceleration;
    int height = 32;
    int width = 32;
    int scale = 1;
    bool willCollide = false;

    int speed = 8;
    Transform();
    Transform(int sc, Entity &mEntity);
    Transform(float x, float y);
    Transform(float x, float y, int h, int w, int sc, Entity &mEntity);
    void update();
};