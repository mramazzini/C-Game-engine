#pragma once
#include <SDL2/SDL.h>
#include <vector>
class Entity;
class ColliderComponent;
class Vector2D;
class TransformComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);
    static bool SAABB(const SDL_Rect &entity, const SDL_Rect &target, const TransformComponent &transformA, const TransformComponent &transformB, Vector2D &contact_point, Vector2D &contact_normal, float &contactTime, float &elapsedTime);
    static float SAABB(const ColliderComponent &colA, const ColliderComponent &colB, const TransformComponent &transformA, const TransformComponent &transformB, float &normalx, float &normaly);
    static void ResolveCollision(Entity *entity, std::vector<Entity *> *colliders);
    static bool RayVsRect(const Vector2D &ray_origin, const Vector2D &ray_dir, const SDL_Rect &target, Vector2D &contact_point, Vector2D &contact_normal, float &t_hit_near);
};
