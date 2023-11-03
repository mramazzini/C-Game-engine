#include "Systems/ColliderSystem.h"
#include "ECS/Core/Core.h"
#include "ECS/Components/Collider.h"

extern Coordinator gCoordinator;

void ColliderSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &collider = gCoordinator.GetComponent<Collider>(e);
        collider.update();
    }
}