#pragma once
#include <string>

#include "Components.h"
#include "../TextureManager.h"
class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture *tex;
    SDL_Rect srcR, desR;

    TransformComponent *transform;
    ColliderComponent(std::string t)
    {
        tag = t;
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

        tex = TextureManager::LoadTexture("assets/collider.png");
        srcR = {0, 0, 32, 32};
        desR = {collider.x, collider.y, collider.w, collider.h};

        // Game::colliders.push_back(this);
    }
    void update() override
    {

        if (tag != "terrain")
        {
            collider.x = static_cast<int>(transform->pos.x);
            collider.y = static_cast<int>(transform->pos.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }

        desR.x = collider.x - Game::camera.x;
        desR.y = collider.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::Draw(tex, srcR, desR, SDL_FLIP_NONE);
    }
};