#include "Systems/ProjectileSystem.h"
#include "Components/Projectile.h"
#include "Components/Transform.h"
#include <vector>
extern Coordinator gCoordinator;
void ProjectileSystem::update()
{
    std::vector<Entity> projectilesToDelete;

    for (Entity e : mEntities)
    {
        Projectile &projectile = gCoordinator.GetComponent<Projectile>(e);
        projectile.update();
        if (!projectile.isActive())
        {
            projectilesToDelete.push_back(e);
        }
    }
    for (int i = 0; i < projectilesToDelete.size(); i++)
    {
        gCoordinator.DestroyEntity(projectilesToDelete[i]);
    }
    projectilesToDelete.clear();
}