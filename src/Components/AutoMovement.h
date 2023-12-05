#pragma once
#include <unordered_map>
#include <functional>
#include "Transform.h"
#include "Sprite.h"
#include "Gravity.h"
extern Coordinator gCoordinator;
class AutoMovement : public Component
{
public:
    AutoMovement();
    bool grounded = false;
    AutoMovement(Entity &mEntity, std::string movementID);

    ~AutoMovement();

    void update();

private:
    std::string movementID;
    Transform *transform;
    Sprite *sprite;
    Gravity *gravity;
    std::unordered_map<std::string, std::int32_t> movementMap = {
        {"idle", 0},
        {"walk", 1},
        {"jump", 2},
    };

    void idle();
    void walk();
    void jump();
};