
#include "Components/Damage.h"
#include <map>
#include "Hitpoint.h"

Damage::~Damage() {}
Damage::Damage() {}

Damage::Damage(int mdamage, bool mfriendly, Entity mentity)
{
    damage = mdamage;
    friendly = mfriendly;
    entity = mentity;
}
void Damage::attack(Entity enemy)
{
    if (!gCoordinator.HasComponent<Hitpoint>(enemy))
    {
        return;
    }
    gCoordinator.GetComponent<Hitpoint>(enemy).takeDamage(damage);
}
bool Damage::isFriendly()
{
    return friendly;
}