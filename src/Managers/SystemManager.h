#pragma once
#include "Systems.h"

#include "Components.h"
#include "Core/Core.h"

class SystemManager
{
public:
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<ColliderSystem> colliderSystem;
    std::shared_ptr<KeyboardControlSystem> keyboardControlSystem;
    std::shared_ptr<DamageSystem> damageSystem;
    std::shared_ptr<HitpointSystem> hitpointSystem;
    std::shared_ptr<GlobalSystem> globalSystem;
    std::shared_ptr<PlayerSystem> playerSystem;
    std::shared_ptr<ProjectileSystem> projectileSystem;
    std::shared_ptr<TransformSystem> transformSystem;
    std::shared_ptr<GravitySystem> gravitySystem;
    std::shared_ptr<AutoMovementSystem> autoMovementSystem;

    SystemManager(Coordinator *gCoordinator);
    void init();
    void update();
    void draw(bool drawColliders);

private:
    Coordinator *gCoordinator;
};