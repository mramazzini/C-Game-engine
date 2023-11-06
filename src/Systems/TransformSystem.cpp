#include "Systems/TransformSystem.h"
#include "Components/Transform.h"

void TransformSystem::update()
{
    for (Entity e : mEntities)
    {
        Transform &transform = gCoordinator.GetComponent<Transform>(e);
        transform.update();
    }
}
