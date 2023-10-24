#pragma once

#include "Components.h"
#include "../Vector2D.h"
class Game;
struct TransformComponent : public Component
{

public:
    Vector2D pos;
    Vector2D velocity;
    Vector2D expectedPos;
    Vector2D expectedVelocity;
    int height = 32;
    int width = 32;
    int scale = 1;
    bool willCollideX = false;
    bool willCollideY = false;
    int speed = 3;

    TransformComponent()
    {
        pos.Zero();
    }
    TransformComponent(int sc)
    {
        pos.x = 400;
        pos.y = 400;
        expectedPos.x = 400;
        expectedPos.y = 400;
        scale = sc;
    }
    TransformComponent(float x, float y)
    {
        pos.x = x;
        pos.y = y;
        expectedPos.x = x;
        expectedPos.y = y;
    }
    TransformComponent(float x, float y, int h, int w, int sc)
    {
        pos.x = x;
        pos.y = y;
        expectedPos.x = x;
        expectedPos.y = y;
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

        pos.x = expectedPos.x;
        pos.y = expectedPos.y;
        expectedPos.x += velocity.x * speed;
        expectedPos.y += velocity.y * speed;
    }
};