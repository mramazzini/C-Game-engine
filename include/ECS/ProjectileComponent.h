#pragma once

#include "Components.h"
#include "../Vector2D.h"
class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int mrange, int mspeed, Vector2D vector)
    {
        velocity = vector;
        distance = 0;
        range = mrange;
        speed = mspeed;
    }
    ~ProjectileComponent(){};

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        transform->velocity = velocity;
    }

    void update() override
    {
        distance += speed;
        // std::cout << transform->pos << std::endl;
        // destroy projectile if exceeding its max range
        if (distance > range)
        {
            entity->destroy();
            // std::cout << "out of range" << std::endl;
        }
        else if ( // destroy projectile if out of bounds
            transform->pos.x > Game::camera.x + Game::camera.w ||
            transform->pos.x < Game::camera.x ||
            transform->pos.y > Game::camera.y + Game::camera.h ||
            transform->pos.y < Game::camera.y)
        {
            // std::cout << "out of bounds" << std::endl;
            entity->destroy();
        }
    }

private:
    TransformComponent *transform;
    Vector2D velocity;
    int range;
    int speed;
    int distance;
};