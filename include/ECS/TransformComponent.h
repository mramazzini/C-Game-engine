#pragma once
#include <iomanip>
#include "Components.h"
#include "../Vector2D.h"
#include <cmath>
#include "../Game.h"
#include "../Collision.h"
struct TransformComponent : public Component
{

public:
    Vector2D pos;
    std::vector<Entity *> colliders;
    Vector2D velocity;

    Vector2D acceleration;
    int height = 32;
    int width = 32;
    int scale = 1;
    bool willCollide = false;

    int speed = 8;

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
        acceleration.Zero();
        colliders = entity->manager->getGroup(Game::groupColliders);
    }
    void update() override
    {
        // friction
        if (scale == 4)
        {

            if (velocity.x > 0 && acceleration.x == 0)
            {
                velocity.x = velocity.x * 0.9;
            }
            else if (velocity.x < 0 && acceleration.x == 0)
            {
                velocity.x = velocity.x * 0.9;
            }
        }

        velocity.x += acceleration.x;
        velocity.y += acceleration.y;

        // Hard limit for maximum velocity
        if (velocity.x > 5)
        {
            velocity.x = 5;
        }
        else if (velocity.x < -5)
        {
            velocity.x = -5;
        }
        if (velocity.y > 5)
        {
            velocity.y = 5;
        }
        else if (velocity.y < -5)
        {
            velocity.y = -5;
        }
        if (scale == 4)
        {

            // std::cout << std::fixed << std::setprecision(2)
            //           << "P: "
            //           << "(" << pos.x + velocity.x * speed << "," << pos.y + velocity.y * speed << ")"
            //           << "V:" << velocity
            //           << "A:" << acceleration << std::endl;
        }
        if (scale == 4)
        {

            // check for player collision TODO: FIX FROM SCALE TO AN ACTUAL IDENTIFER FOR PLAYER
            Collision::ResolveCollision(entity, &colliders);
        }
        pos.x += velocity.x * speed;
        pos.y += velocity.y * speed;

        acceleration.Zero();
    }
};