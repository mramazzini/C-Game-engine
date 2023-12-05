#pragma once

#include "Core/Core.h"

extern Coordinator gCoordinator;

class AutoMovementSystem : public System
{
public:
    void update();
};