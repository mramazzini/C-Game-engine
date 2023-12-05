#pragma once
#include "Core/Core.h"
#include <map>
#include "Hitpoint.h"

extern Coordinator gCoordinator;
class Damage : public Component
{
public:
    ~Damage();
    Damage();

    Damage(int mdamage, bool mfriendly, Entity mentity);
    void attack(Entity enemy);
    bool isFriendly();

private:
    int damage;
    bool friendly = false;
    Entity entity;
};
