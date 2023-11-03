#pragma once

#include "ECS/Core/Core.h"

extern Coordinator gCoordinator;

class DamageSystem : public System
{
public:
    void update();
};