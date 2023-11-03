#pragma once
#include "Transform.h"
#include "Core/Core.h"
#include "Game.h"
#include "Managers.h"

extern Coordinator gCoordinator;
class Collider : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    SDL_Rect hitbox;

    SDL_Rect srcR, desR;

    Transform *transform;

    Collider();

    Collider(std::string t, Entity &mEntity);

    Collider(std::string t, int xpos, int ypos, int size, Entity &mEntity);

    void update();

    void draw();

    void setCollider();
};
