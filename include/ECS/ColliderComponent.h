#pragma once
#include <string>

#include "Components.h"
#include "../TextureManager.h"
#include "../HitboxManager.h"
#include "../Game.h"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    SDL_Rect hitbox;
    SDL_Texture *tex;
    SDL_Rect srcR, desR;

    TransformComponent *transform;
    ColliderComponent(std::string t)
    {
        tag = t;
        setCollider();
    }

    ColliderComponent(std::string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }
    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::LoadTexture("assets/images/collider.png");
        srcR = {0, 0, 32, 32};
        desR = {collider.x, collider.y, collider.w, collider.h};
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

    void draw() override
    {

        TextureManager::Draw(tex, srcR, desR, SDL_FLIP_NONE);
    }

    void setCollider()
    {
        collider = hitbox = *(Game::hitboxes->getHitbox(tag));
    }
};