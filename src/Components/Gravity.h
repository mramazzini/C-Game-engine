#pragma once

#include "Core/Core.h"
#include "Transform.h"
extern Coordinator gCoordinator;
class Gravity : public Component
{
public:
    Gravity();
    bool grounded = false;
    Gravity(Entity &mEntity);
    ~Gravity();

    void update();

private:
    Transform *transform;
};