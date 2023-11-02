#pragma once
#include "Transform.h"
#include "ECS/Core/Core.h"
#include "Game.h"

#include "TextureManager.h"
#include "AssetManager.h"
#include "HitboxManager.h"

extern Coordinator gCoordinator;
class Collider : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    SDL_Rect hitbox;

    SDL_Rect srcR, desR;

    Transform *transform;

    Collider()
    {
    }
    Collider(std::string t, Entity &mEntity)
    {
        entity = mEntity;
        tag = t;
        setCollider();
        transform = &gCoordinator.GetComponent<Transform>(entity);
    }

    Collider(std::string t, int xpos, int ypos, int size, Entity &mEntity)
    {
        entity = mEntity;
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void update() override
    {

        if (tag != "terrain")
        {
            collider.x = static_cast<int>(transform->pos.x) + hitbox.x * transform->scale;
            collider.y = static_cast<int>(transform->pos.y) + hitbox.y * transform->scale;
            collider.w = desR.w = hitbox.w * transform->scale;
            collider.h = desR.h = hitbox.h * transform->scale;
        }

        desR.x = collider.x - Game::camera.x;
        desR.y = collider.y - Game::camera.y;
    }

    void draw()
    {

        //  /std::cout << desR.x << " " << desR.y << " " << desR.w << " " << desR.h << std::endl;
        TextureManager::Draw(Game::assets->getTexture("collider"), srcR, desR, SDL_FLIP_NONE);
    }

    void setCollider()
    {
        collider = hitbox = *(Game::hitboxes->getHitbox(tag));
    }
};
