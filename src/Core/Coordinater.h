#pragma once
#include "ComponentCore.h"
#include "EntityCore.h"
#include <iostream>
#include "SystemCore.h"
#include "Types.h"
#include <memory>

class Coordinator
{
public:
    void Init()
    {
        // Create pointers to each manager
        mComponentCore = std::make_unique<ComponentCore>();
        mEntityCore = std::make_unique<EntityCore>();
        mSystemCore = std::make_unique<SystemCore>();
    }

    // Entity methods
    Entity CreateEntity()
    {
        return mEntityCore->CreateEntity();
    }

    void DestroyEntity(Entity entity)
    {
        mEntityCore->DestroyEntity(entity);

        mComponentCore->EntityDestroyed(entity);

        mSystemCore->EntityDestroyed(entity);
    }
    void DestroyEntities(std::set<Entity> entities)
    {
        for (Entity e : entities)
        {
            DestroyEntity(e);
        }
    }

    // Component methods
    template <typename T>
    void RegisterComponent()
    {
        mComponentCore->RegisterComponent<T>();
    }

    template <typename T>
    void AddComponent(Entity entity, T component)
    {
        mComponentCore->AddComponent<T>(entity, component);

        auto signature = mEntityCore->GetSignature(entity);
        signature.set(mComponentCore->GetComponentType<T>(), true);
        mEntityCore->SetSignature(entity, signature);

        mSystemCore->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    void RemoveComponent(Entity entity)
    {
        mComponentCore->RemoveComponent<T>(entity);

        auto signature = mEntityCore->GetSignature(entity);
        signature.set(mComponentCore->GetComponentType<T>(), false);
        mEntityCore->SetSignature(entity, signature);

        mSystemCore->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    bool HasComponent(Entity entity)
    {
        return mComponentCore->HasComponent<T>(entity);
    }

    template <typename T>
    T &GetComponent(Entity entity)
    {
        return mComponentCore->GetComponent<T>(entity);
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        return mComponentCore->GetComponentType<T>();
    }

    // System methods
    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return mSystemCore->RegisterSystem<T>();
    }

    template <typename T>
    void SetSystemSignature(Signature signature)
    {
        mSystemCore->SetSignature<T>(signature);
    }
    int GetEntityCount()
    {
        return mEntityCore->GetEntityCount();
    }
    int GetComponentCount()
    {
        return mComponentCore->GetComponentCount();
    }

private:
    std::unique_ptr<ComponentCore> mComponentCore;
    std::unique_ptr<EntityCore> mEntityCore;
    std::unique_ptr<SystemCore> mSystemCore;
};