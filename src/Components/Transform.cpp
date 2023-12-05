#include "Components.h"
#include "Utils/Collision.h"
#include "Game.h"
#include "Systems/ColliderSystem.h"
#include "Managers/SystemManager.h"
extern Coordinator gCoordinator;

Transform::Transform()
{
    pos.Zero();
    velocity.Zero();
    acceleration.Zero();
}

Transform::Transform(float x, float y, int sc, Entity &mEntity)
{
    pos.x = x;
    pos.y = y;
    entity = mEntity;
    scale = sc;
    velocity.Zero();
    acceleration.Zero();
    colliders = &Game::systems->colliderSystem->mEntities;
}

Transform::Transform(float x, float y, int h, int w, int sc, Entity &mEntity)
{
    pos.x = x;
    pos.y = y;
    height = h;
    width = w;
    scale = sc;
    velocity.Zero();
    acceleration.Zero();
}

void Transform::update()
{
    // Early return
    if (velocity.x == 0 && velocity.y == 0 && acceleration.x == 0 && acceleration.y == 0)
    {
        return;
    }
    // friction
    if (scale == 4)
    {

        if (velocity.x > 0 && acceleration.x == 0)
        {
            velocity.x = velocity.x * 0.8;
        }
        else if (velocity.x < 0 && acceleration.x == 0)
        {
            velocity.x = velocity.x * 0.8;
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
        //           <<
        //           << "V:" << velocity
        //           << "A:" << acceleration << std::endl;
    }
    if (scale == 4)
    {

        // check for player collision TODO: FIX FROM SCALE TO AN ACTUAL IDENTIFER FOR PLAYER
        Collision::ResolveCollision(entity, colliders);
    }
    pos.x += velocity.x * speed;
    pos.y += velocity.y * speed;

    acceleration.Zero();
}
