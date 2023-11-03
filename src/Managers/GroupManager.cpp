#include "GroupManager.h"

GroupManager::GroupManager(Coordinator *gCoordinator) : gCoordinator(gCoordinator) {}

void GroupManager::init()
{
    std::cout << "Initializing Grouped Component Systems" << std::endl;
    {
        renderSystem = gCoordinator->RegisterSystem<RenderSystem>();
        Signature signature;
        signature.set(gCoordinator->GetComponentType<Sprite>());
        gCoordinator->SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->init();
    //
    {
        colliderSystem = gCoordinator->RegisterSystem<ColliderSystem>();
        Signature signature;
        signature.set(gCoordinator->GetComponentType<Collider>());
        gCoordinator->SetSystemSignature<ColliderSystem>(signature);
    }
    colliderSystem->init();
    {
        keyboardControlSystem = gCoordinator->RegisterSystem<KeyboardControlSystem>();
        Signature signature;
        signature.set(gCoordinator->GetComponentType<Keyboard>());
        gCoordinator->SetSystemSignature<KeyboardControlSystem>(signature);
    }
    keyboardControlSystem->init();
    {
        damageSystem = gCoordinator->RegisterSystem<DamageSystem>();
        Signature signature;
        signature.set(gCoordinator->GetComponentType<Damage>());
        gCoordinator->SetSystemSignature<DamageSystem>(signature);
    }
    damageSystem->init();
    {
        hitpointSystem = gCoordinator->RegisterSystem<HitpointSystem>();
        Signature signature;
        signature.set(gCoordinator->GetComponentType<Hitpoint>());
        gCoordinator->SetSystemSignature<HitpointSystem>(signature);
    }
    hitpointSystem->init();
    {
        globalSystem = gCoordinator->RegisterSystem<GlobalSystem>();
        Signature signature;

        gCoordinator->SetSystemSignature<GlobalSystem>(signature);
    }
    globalSystem->init();
    {
        playerSystem = gCoordinator->RegisterSystem<PlayerSystem>();
        Signature signature;
        signature.set(gCoordinator->GetComponentType<Player>());
        gCoordinator->SetSystemSignature<PlayerSystem>(signature);
    }
    playerSystem->init();
}

void GroupManager::update()
{
    keyboardControlSystem->update();
    colliderSystem->update();
    damageSystem->update();
    playerSystem->update();
    renderSystem->update();
}

void GroupManager::draw()
{
    renderSystem->draw();
}
