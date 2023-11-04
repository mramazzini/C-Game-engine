#include "Systems/DamageSystem.h"
#include "Collision.h"
#include "Game.h"
#include "Components.h"
#include "Managers/SystemManager.h"

extern Coordinator gCoordinator;

void DamageSystem::update()
{
    std::vector<Entity> entitiesToDestroy;
    for (Entity e : mEntities)
    {

        auto &damage = gCoordinator.GetComponent<Damage>(e);
        auto &collider = gCoordinator.GetComponent<Collider>(e);

        for (Entity hitpointEntity : Game::systems->hitpointSystem->mEntities)
        {
            auto &otherCollider = gCoordinator.GetComponent<Collider>(hitpointEntity);
            auto &otherHitpoint = gCoordinator.GetComponent<Hitpoint>(hitpointEntity);

            if (damage.isFriendly() == otherHitpoint.isFriendly())
            {
                // if both entities are friendly or both are not friendly, skip
                // This prevents friendly fire for both players and enemies,
                // also skipping the Heavy collision detection algorithm
                continue;
            }
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