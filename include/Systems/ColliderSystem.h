#pragma once

#include "ECS/Core/Core.h"

extern Coordinator gCoordinator;

class ColliderSystem : public System
{
public:
    void update();
};