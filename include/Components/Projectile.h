#pragma once

#include "Core/Core.h"
#include "Vector2D.h"
#include "Transform.h"
class Projectile : public Component
{
public:
    Projectile() {}
    Projectile(int mrange, int mspeed, Vector2D vector, Entity mEntity)
    {
        velocity = vector;
        distance = 0;
        range = mrange;
        speed = mspeed;
        entity = mEntity;
        transform = &gCoordinator.GetComponent<Transform>(entity);
        transform->velocity = velocity;
    }
    ~Projectile(){};

    void update() override
    {
        distance += speed;
        // std::cout << transform->pos << std::endl;
        // destroy projectile if exceeding its max range
        if (distance > range)
        {
            gCoordinator.DestroyEntity(entity);
            // std::cout << "out of range" << std::endl;
        }
        else if ( // destroy projectile if out of bounds
            transform->pos.x > Game::camera.x + Game::camera.w ||
            transform->pos.x < Game::camera.x ||
            transform->pos.y > Game::camera.y + Game::camera.h ||
            transform->pos.y < Game::camera.y)
        {
            // std::cout << "out of bounds" << std::endl;
            gCoordinator.DestroyEntity(entity);
        }
    }

private:
    Transform *transform;
    Vector2D velocity;
    Entity entity;
    int range;
    int speed;
    int distance;
};