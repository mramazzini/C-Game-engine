#include "../include/Collision.h"
#include "../include/ECS/ColliderComponent.h"
#include <cmath>
#include <vector>

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y)
    {
        return true;
    }
    return false;
}
bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    return false;
}
bool Collision::RayVsRect(const Vector2D &ray_origin, const Vector2D &ray_dir, const SDL_Rect &target, Vector2D &contact_point, Vector2D &contact_normal, float &t_hit_near)
{
    contact_normal = {0, 0};
    contact_point = {0, 0};
    Vector2D t_near = Vector2D((target.x - ray_origin.x) / ray_dir.x, (target.y - ray_origin.y) / ray_dir.y);
    Vector2D t_far = Vector2D((target.x + target.w - ray_origin.x) / ray_dir.x, (target.y + target.h - ray_origin.y) / ray_dir.y);

    if (std::isnan(t_far.y) || std::isnan(t_far.x))
        return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x))
        return false;

    // Sort distances
    if (t_near.x > t_far.x)
    {
        std::swap(t_near.x, t_far.x);
    }
    if (t_near.y > t_far.y)
    {
        std::swap(t_near.y, t_far.y);
    }
    // Early rejection
    if (t_near.x > t_far.y || t_near.y > t_far.x)
    {
        return false;
    }
    // Closest 'time' will be the first contact
    t_hit_near = std::max(t_near.x, t_near.y);
    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);
    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
    {
        return false;
    }
    // Contact point of collision from parametric line equation
    contact_point = Vector2D(ray_origin.x + (ray_dir.x * t_hit_near), ray_origin.y + (ray_dir.y * t_hit_near));

    if (t_near.x > t_near.y)
    {
        if (ray_dir.x < 0)
        {
            contact_normal = Vector2D(1, 0);
        }
        else
        {
            contact_normal = Vector2D(-1, 0);
        }
    }
    else if (t_near.x < t_near.y)
    {
        if (ray_dir.y < 0)
        {
            contact_normal = Vector2D(0, 1);
        }
        else
        {
            contact_normal = Vector2D(0, -1);
        }
    }
    return true;
}
bool Collision::SAABB(const SDL_Rect &entity, const SDL_Rect &target, const TransformComponent &transformA, const TransformComponent &transformB, Vector2D &contact_point, Vector2D &contact_normal, float &contactTime, float &elapsedTime)
{
    if (transformA.velocity.x == 0 && transformA.velocity.y == 0)
        return false;
    SDL_Rect expandedTarget;
    expandedTarget.x = target.x - (entity.w / 2);
    expandedTarget.y = target.y - (entity.h / 2);
    expandedTarget.w = target.w + entity.w;
    expandedTarget.h = target.h + entity.h;

    Vector2D in = Vector2D(entity.x + entity.w / 2 * elapsedTime, entity.y + entity.h / 2 * elapsedTime);
    if (RayVsRect(in, Vector2D(transformA.velocity.x * transformA.speed, transformA.velocity.y * transformA.speed), expandedTarget, contact_point, contact_normal, contactTime))
    {

        if (contactTime >= 0.0f && contactTime < 1.0f)
        {

            return true;
        }
    }
    return false;
}

void Collision::ResolveCollision(Entity *entity, std::vector<Entity *> *colliders)
{
    std::vector<std::pair<int, float>> z;
    int i = 0;
    auto &transformEntity = entity->getComponent<TransformComponent>();
    auto &entityCol = entity->getComponent<ColliderComponent>().collider;
    for (auto &other : *colliders)
    {

        auto &transformOther = other->getComponent<TransformComponent>();
        auto &otherCol = other->getComponent<ColliderComponent>().collider;

        float contactTime = 0.0f;
        float elapsedTime = 1.0f;
        Vector2D contactPoint, contactNormal;

        if (SAABB(entityCol, otherCol, transformEntity, transformOther, contactPoint, contactNormal, contactTime, elapsedTime))
        {
            z.push_back({i, contactTime});
        }
        i++;
    }

    std::sort(z.begin(), z.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b)
              { return a.second < b.second; });

    for (auto &j : z)
    {

        auto &transformOther = colliders->at(j.first)->getComponent<TransformComponent>();

        auto &otherCol = colliders->at(j.first)->getComponent<ColliderComponent>().collider;

        float contactTime = 0.0f;
        float elapsedTime = 1.0f;
        Vector2D contactPoint, contactNormal;
        if (SAABB(entity->getComponent<ColliderComponent>().collider, colliders->at(j.first)->getComponent<ColliderComponent>().collider, entity->getComponent<TransformComponent>(), colliders->at(j.first)->getComponent<TransformComponent>(), contactPoint, contactNormal, contactTime, elapsedTime))
        {
            entity->getComponent<TransformComponent>().velocity.x += contactNormal.x * std::abs(entity->getComponent<TransformComponent>().velocity.x) * (1.0f - j.second);
            entity->getComponent<TransformComponent>().velocity.y += contactNormal.y * std::abs(entity->getComponent<TransformComponent>().velocity.y) * (1.0f - j.second);
            if (contactNormal.y == -1)
            { // if entity hits the floor, set grounded to true
                entity->getComponent<GravityComponent>().grounded = true;
            }
        }
    }
}