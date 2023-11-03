#include "Systems/TransformSystem.h"
#include "Components/Transform.h"

void TransformSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &transform = gCoordinator.GetComponent<Transform>(e);
        transform.update();
    }
}
