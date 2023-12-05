#pragma once
#include "Utils/Vector2D.h"
#include <set>
#include "Core/Core.h"
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

    Transform(float x, float y, int sc, Entity &mEntity);               // Entity
    Transform(float x, float y, int h, int w, int sc, Entity &mEntity); // Tile
    void update();
};