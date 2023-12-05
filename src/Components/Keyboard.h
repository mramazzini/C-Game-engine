#pragma once
#include <vector>
#include <algorithm>
#include "Game.h"

#include "Managers.h"
class Sprite;
class Transform;
class Gravity;
extern Coordinator gCoordinator;
class Keyboard : public Component
{
public:
    Transform *transform;
    Sprite *sprite;
    Gravity *gravity;

    std::vector<SDL_Keycode> keys;
    Keyboard();
    Keyboard(Entity mentity);

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    bool updateKeys();
};