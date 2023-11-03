#pragma once
#include "ECS/Core/Core.h"
#include "Game.h"
#include "Components.h"
#include <vector>
extern Coordinator gCoordinator;
class RenderSystem : public System
{
public:
    bool drawHitboxes = true;
    Entity playerEntity = 10000;
    std::vector<Entity> projectiles;
    void update()
    {
        for (Entity e : mEntities)
        {
            auto &sprite = gCoordinator.GetComponent<Sprite>(e);
            sprite.update();
        }
    }
    void draw() override
    {

        for (const Entity &entity : mEntities)
        {
            auto &transform = gCoordinator.GetComponent<Transform>(entity);
            auto &sprite = gCoordinator.GetComponent<Sprite>(entity);

            if (drawHitboxes)
            {
                sprite.draw();
            }
            else if (!gCoordinator.HasComponent<Collider>(entity))
            {
                sprite.draw();
            }
            if (gCoordinator.HasComponent<Projectile>(entity))
            {
                projectiles.push_back(entity);
            }
            if (gCoordinator.HasComponent<Player>(entity))
            {
                playerEntity = entity;
            }
        }

        for (auto &projectile : projectiles)
        {
            auto &p = gCoordinator.GetComponent<Projectile>(projectile);

            p.update();
            if (gCoordinator.HasComponent<Transform>(projectile))
            {
                gCoordinator.GetComponent<Transform>(projectile).update();
            }
        }
        projectiles.clear();
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
};