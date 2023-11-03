#pragma once

#include "Core/Core.h"

extern Coordinator gCoordinator;

class ColliderSystem : public System
{
public:
    void update();
};