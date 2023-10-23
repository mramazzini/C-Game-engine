#pragma once
#include "Components.h"
#include <map>

class DamageComponent : public Component
{
public:
    ~DamageComponent() {}

    DamageComponent(int mdamage, bool mfriendly)
    {
        damage = mdamage;
        friendly = mfriendly;
    }
    void attack(Entity *enemy)
    {
        if (!enemy->hasComponent<HitpointComponent>())
        {
            return;
        }
        enemy->getComponent<HitpointComponent>().takeDamage(damage);
    }

private:
    int damage;
    bool friendly;
};
