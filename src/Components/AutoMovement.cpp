#include "AutoMovement.h"
#include <string>

#include "Core.h"

AutoMovement::AutoMovement(){};

AutoMovement::AutoMovement(Entity &mEntity, std::string movementID)
{
    entity = mEntity;
    transform = &gCoordinator.GetComponent<Transform>(entity);
    sprite = &gCoordinator.GetComponent<Sprite>(entity);
    if (gCoordinator.HasComponent<Gravity>(entity))
    {
        gravity = &gCoordinator.GetComponent<Gravity>(entity);
    }

    this->movementID = movementID;
}
AutoMovement::~AutoMovement(){};

void AutoMovement::update()
{
    auto it = movementMap.find(movementID);
    if (it != movementMap.end())
    {
        switch (it->second)
        {
        case 0:
            idle();
            break;
        case 1:
            walk();
            break;
        case 2:
            jump();
            break;
        }
    }
    else
    {
        // Handle the case where movementID doesn't match any of the expected values
    }
}

void AutoMovement::idle()
{
    // Do nothing
}
void AutoMovement::walk()
{
    this->transform->velocity.x += 0.1;
    std::cout << "walk" << std::endl;
}
void AutoMovement::jump()
{
    if (gCoordinator.HasComponent<Gravity>(entity) && gravity)
    {
        if (gravity->grounded == true)
        {
            transform->velocity.y = -2.5;

            gravity->grounded = false;
            // sprite->play("walk");
        }
    }
}