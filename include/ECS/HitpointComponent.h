#pragma once

#include "Components.h"

class HitpointComponent : public Component
{
public:
    HitpointComponent(int hp)
    {
        texture = Game::assets->getTexture("hpbar");
        currentHitpoints = hp;
        maxHitpoints = hp;
        percentageHp = 1;
    }
    ~HitpointComponent() {}
    void takeDamage(int dmg)
    {
        currentHitpoints -= dmg;
        percentageHp = currentHitpoints / maxHitpoints;
    }
    void heal(int hp)
    {
        currentHitpoints += hp;
        percentageHp = currentHitpoints / maxHitpoints;
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRectG.x = 0;
        srcRectG.y = 0;
        srcRectG.w = 32;
        srcRectG.h = 10;

        srcRectR.x = 32;
        srcRectR.y = 0;
        srcRectR.w = 32;
        srcRectR.h = 10;

        srcRectB.x = 64;
        srcRectB.y = 0;
        srcRectB.w = 32;
        srcRectB.h = 10;

        // hp bar is as wide as the entity, but has a height of 10
        destRectRB.w = transform->width;
        destRectRB.h = 10;

        destRectG.h = 10;
    }
    void draw() override
    {
        // Draw Red bar
        TextureManager::Draw(texture, srcRectR, destRectRB, SDL_FLIP_NONE);
        // Draw Green bar
        TextureManager::Draw(texture, srcRectG, destRectG, SDL_FLIP_NONE);
        // Draw Outline
        TextureManager::Draw(texture, srcRectB, destRectRB, SDL_FLIP_NONE);
    }
    void update() override
    {
        destRectRB.x = destRectG.x = static_cast<int>(transform->pos.x) - Game::camera.x;
        destRectRB.y = destRectG.y = static_cast<int>(transform->pos.y) - Game::camera.y - 10 * transform->scale;
        destRectRB.w = transform->width * transform->scale;
        destRectRB.h = destRectG.h = 10 * transform->scale;
        destRectG.w = static_cast<int>((transform->width * transform->scale) * percentageHp);
        std::cout << percentageHp << std::endl;
    }

private:
    SDL_Texture *texture;
    int maxHitpoints;
    int currentHitpoints;
    float percentageHp;
    TransformComponent *transform;

    // Green bar
    SDL_Rect srcRectG;
    // Red bar
    SDL_Rect srcRectR;
    // Black outline
    SDL_Rect srcRectB;

    // Dest Rect for redbar an black outline
    SDL_Rect destRectRB;

    // Green bar gets rendered based off of entities hp
    SDL_Rect destRectG;
};
