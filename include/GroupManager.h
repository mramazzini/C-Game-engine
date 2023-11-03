#pragma once
#include "Systems.h"

#include "Components.h"
#include "ECS/Core/Core.h"

class GroupManager
{
public:
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<ColliderSystem> colliderSystem;
    std::shared_ptr<KeyboardControlSystem> keyboardControlSystem;
    std::shared_ptr<DamageSystem> damageSystem;
    std::shared_ptr<HitpointSystem> hitpointSystem;
    std::shared_ptr<GlobalSystem> globalSystem;
    std::shared_ptr<PlayerSystem> playerSystem;

    GroupManager(Coordinator *gCoordinator);
    void init();
    void update();
    void draw();

private:
    Coordinator *gCoordinator;
};