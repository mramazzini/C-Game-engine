#pragma once

#include "Core/Core.h"

// class TransformComponent;
// class GravityComponent;
// class ColliderComponent;

extern Coordinator gCoordinator;

class TransformSystem : public System
{

public:
    void update();
};