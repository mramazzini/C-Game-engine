#pragma once
#include "Game.h"
#include "Core/Core.h"
#include "Managers/AssetManager.h"
#include "Managers/CameraManager.h"
#include "Transform.h"
extern Coordinator gCoordinator;
class Hitpoint : public Component
{
public:
    Hitpoint() {}
    Hitpoint(int hp, bool friendly, Entity &mEntity)
    {
        entity = mEntity;
        this->friendly = friendly;
        texture = Game::assets->getTexture("hpbar");
        currentHitpoints = hp;
        maxHitpoints = hp;
        percentageHp = 1.0f;

        transform = &gCoordinator.GetComponent<Transform>(entity);

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
    ~Hitpoint() {}
    void takeDamage(int dmg)
    {

        // std::cout << "Took" << dmg << " damage." << std::endl;
        // std::cout << "Had " << currentHitpoints << "/" << maxHitpoints << " HP." << std::endl;
        // std::cout << "Percentage HP: " << percentageHp * 100 << std::endl;
        currentHitpoints -= dmg;
        percentageHp = static_cast<float>(currentHitpoints) / maxHitpoints;
        // std::cout << "Has " << currentHitpoints << "/" << maxHitpoints << " HP." << std::endl;
        // std::cout << "Percentage HP: " << percentageHp * 100 << std::endl;
    }
    void heal(int hp)
    {
        currentHitpoints += hp;
        percentageHp = currentHitpoints / maxHitpoints;
    }

    void draw()
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
        destRectRB.x = destRectG.x = static_cast<int>(transform->pos.x) - Game::camera->getCamera().x;
        destRectRB.y = destRectG.y = static_cast<int>(transform->pos.y) - Game::camera->getCamera().y - 10 * transform->scale;
        destRectRB.w = transform->width * transform->scale;
        destRectRB.h = destRectG.h = 10 * transform->scale;
        destRectG.w = static_cast<int>((transform->width * transform->scale) * percentageHp);
    }
    bool isFriendly()
    {
        return friendly;
    }

private:
    SDL_Texture *texture;
    int maxHitpoints;
    int currentHitpoints;
    float percentageHp;
    Transform *transform;
    Entity entity;
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

    bool friendly = false;
};