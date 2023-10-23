#pragma once

#include "Components.h"
#include "../Vector2D.h"
struct TransformComponent : public Component
{

public:
    Vector2D pos;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    TransformComponent()
    {
        pos.Zero();
    }
    TransformComponent(int sc)
    {
        pos.x = 400;
        pos.y = 400;
        scale = sc;
    }
    TransformComponent(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }
    TransformComponent(float x, float y, int h, int w, int sc)
    {
        pos.x = x;
        pos.y = y;
        height = h;
        width = w;
        scale = sc;
    }
    void init() override
    {
        velocity.Zero();
    }
    void update() override
    {
        pos.x += velocity.x * speed;
        pos.y += velocity.y * speed;
    }
};