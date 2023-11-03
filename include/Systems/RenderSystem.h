#pragma once
#include "Core/Core.h"
#include "Game.h"

#include <vector>

class RenderSystem : public System
{
public:
    bool drawHitboxes = true;
    Entity playerEntity = 10000;

    void update();
    void draw() override;
};