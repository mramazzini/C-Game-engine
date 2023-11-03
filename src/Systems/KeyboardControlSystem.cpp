#include "Systems/KeyboardControlSystem.h"
#include "ECS/Components/Keyboard.h"

void KeyboardControlSystem::update()
{
    for (Entity e : mEntities)
    {
        Keyboard &keyboard = gCoordinator.GetComponent<Keyboard>(e);
        if (keyboard.updateKeys())
        {
            return;
        }
    }
}