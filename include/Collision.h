#pragma once
#include <SDL2/SDL.h>
class Entity;
class ColliderComponent;
class Vector2D;
class TransformComponent;
class Collision
{
public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);
    static void ResolveCollision(Entity *entity, const SDL_Rect &wallCol);
};
