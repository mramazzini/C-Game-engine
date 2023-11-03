#pragma once

#include "Types.h"
#include <set>
// Meant to be inherited from
class System
{
public:
    std::set<Entity> mEntities;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~System() {}
};