#pragma once
#include "Core/Core.h"
class PlayerSystem : public System
{
public:
    void update();
    void draw();
    Entity getPlayer();
};