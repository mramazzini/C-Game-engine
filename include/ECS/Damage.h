#pragma once
#include "Core/Core.h"
#include <map>
#include "Hitpoint.h"

extern Coordinator gCoordinator;
class Damage : public Component
{
public:
    ~Damage() {}
    Damage() {}

    Damage(int mdamage, bool mfriendly, Entity mentity)
    {
        damage = mdamage;
        friendly = mfriendly;
        entity = mentity;
    }
    void attack(Entity enemy)
    {
        if (!gCoordinator.HasComponent<Hitpoint>(enemy))
        {
            return;
        }
        gCoordinator.GetComponent<Hitpoint>(enemy).takeDamage(damage);
    }

private:
    int damage;
    bool friendly;
    Entity entity;
};
