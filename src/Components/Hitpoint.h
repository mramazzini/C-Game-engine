#pragma once

#include "Core/Core.h"
#include <SDL2/SDL.h>
#include "Transform.h"
extern Coordinator gCoordinator;
class Hitpoint : public Component
{
public:
    Hitpoint();
    Hitpoint(int hp, bool friendly, Entity &mEntity);
    ~Hitpoint();
    void takeDamage(int dmg); // std::cout << "Percentage HP: " << percentageHp * 100 << std::endl;
    void heal(int hp);

    void draw();
    void update();
    bool isFriendly();

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