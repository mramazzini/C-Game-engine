#include "Systems/ColliderSystem.h"
#include "Core/Core.h"
#include "Components/Collider.h"
#include "Game.h"
extern Coordinator gCoordinator;

void ColliderSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &collider = gCoordinator.GetComponent<Collider>(e);
        collider.update();
    }
}
void ColliderSystem::draw()
{
    if (!Game::devMode)
    {
        return;
    }
    for (Entity e : mEntities)
    {
        auto &collider = gCoordinator.GetComponent<Collider>(e);

        collider.draw();
    }
}