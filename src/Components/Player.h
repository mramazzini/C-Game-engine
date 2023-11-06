#pragma once
#include "Core/Core.h"

class Player : public Component
{
public:
    Player();
    ~Player();
    Player(Entity ent);

    bool updatePlayer();
};