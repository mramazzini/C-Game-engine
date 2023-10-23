#pragma once

#include "Components.h"

class HitpointComponent : public Component
{
public:
    HitpointComponent(int hp)
    {
        // transform = &entity->getComponent<TransformComponent>();
        // texture = Game::assets->getTexture("hpbar");
        hitpoints = hp;
        // srcRect.x = transform->pos.x;
        // srcRect.y = transform->pos.y;
        // srcRect.w = transform->width;
        // srcRect.h = 10;
    }
    ~HitpointComponent() {}
    void takeDamage(int dmg)
    {
        hitpoints -= dmg;
    }
    // void draw() override
    // {
    //     TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    // }

private:
    SDL_Texture *texture;
    int hitpoints;
    TransformComponent *transform;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};
