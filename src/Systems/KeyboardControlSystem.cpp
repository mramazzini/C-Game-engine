#include "Systems/KeyboardControlSystem.h"
#include "Components/Keyboard.h"

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