#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "ECS/Core/Types.h"
#include <set>

class Transform;
class Collider;

class Vector2D;

class Collision
{
public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
    static bool AABB(const Collider &colA, const Collider &colB);
    static bool SAABB(const SDL_Rect &entity, const SDL_Rect &target, const Transform &transformA, const Transform &transformB, Vector2D &contact_point, Vector2D &contact_normal, float &contactTime, float &elapsedTime);
    static float SAABB(const Collider &colA, const Collider &colB, const Transform &transformA, const Transform &transformB, float &normalx, float &normaly);
    static void ResolveCollision(Entity entity, std::set<Entity> *colliders);
    static bool RayVsRect(const Vector2D &ray_origin, const Vector2D &ray_dir, const SDL_Rect &target, Vector2D &contact_point, Vector2D &contact_normal, float &t_hit_near);
};
