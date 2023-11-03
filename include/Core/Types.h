#pragma once
// EXPLANATION OF WHOLE ECS SYSTEM https://austinmorlan.com/posts/entity_component_system/

#include <bitset>
#include <cstdint>

// ECS
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

class Component
{
public:
    Entity entity;

    virtual ~Component() = default;
    virtual void update() {}
};
