#include "Systems/RenderSystem.h"
#include "Core/Core.h"
#include "Game.h"
#include "Components.h"
extern Coordinator gCoordinator;
void RenderSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &sprite = gCoordinator.GetComponent<Sprite>(e);
        sprite.update();
    }
}
void RenderSystem::draw()
{

    for (const Entity &entity : mEntities)
    {

        auto &sprite = gCoordinator.GetComponent<Sprite>(entity);

        if (drawHitboxes)
        {
            sprite.draw();
        }
        else if (!gCoordinator.HasComponent<Collider>(entity))
        {
            sprite.draw();
        }

        if (gCoordinator.HasComponent<Player>(entity))
        {
            playerEntity = entity;
        }
    }

    if (playerEntity != 10000)
    {
        gCoordinator.GetComponent<Sprite>(playerEntity).draw();
        gCoordinator.GetComponent<Collider>(playerEntity).draw();
        gCoordinator.GetComponent<Hitpoint>(playerEntity).draw();
    }
    else
    {
        std::cerr << "Cannot find Player Entity" << std::endl;
    }
}