#pragma once
#include "ECS/Core/Core.h"
#include "Game.h"

#include <vector>

class RenderSystem : public System
{
public:
    bool drawHitboxes = true;
    Entity playerEntity = 10000;
    std::vector<Entity> projectiles;
    void update();
    void draw() override;
};