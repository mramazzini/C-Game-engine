#pragma once

#include "../ECS/Core/Core.h"
#include "../Collision.h"
#include "../Game.h"
#include "../Systems/HitpointSystem.h"
extern Coordinator gCoordinator;

class DamageSystem : public System
{
public:
    void update()
    {
        std::vector<Entity> entitiesToDestroy;
        for (Entity e : mEntities)
        {

            auto &damage = gCoordinator.GetComponent<Damage>(e);
            auto &collider = gCoordinator.GetComponent<Collider>(e);

            for (Entity hitpointEntity : Game::hitpointSystem->mEntities)
            {
                auto &otherCollider = gCoordinator.GetComponent<Collider>(hitpointEntity);
                if (Collision::AABB(collider, otherCollider))
                {
                    damage.attack(hitpointEntity);
                    entitiesToDestroy.push_back(e);
                }
            }
        }
        for (Entity e : entitiesToDestroy)
        {
            gCoordinator.DestroyEntity(e);
        }
    }
};