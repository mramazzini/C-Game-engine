#include "Systems/PlayerSystem.h"
#include "Core/Core.h"
#include "Components.h"

void PlayerSystem::update()
{
    for (Entity e : mEntities)
    {
        if (gCoordinator.GetComponent<Player>(e).updatePlayer())
        {
            return;
        }
    }
}

void PlayerSystem::draw()
{
    for (Entity e : mEntities)
    {
        gCoordinator.GetComponent<Sprite>(e).draw();
        gCoordinator.GetComponent<Collider>(e).draw();
        gCoordinator.GetComponent<Hitpoint>(e).draw();
    }
}
Entity PlayerSystem::getPlayer()
{
    for (Entity e : mEntities)
    {
        return e;
    }
    return -1;
}