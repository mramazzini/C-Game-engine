#include "../include/Collision.h"
#include "../include/ECS/ColliderComponent.h"

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

void Collision::ResolveCollision(Entity *entity, const SDL_Rect &wallCol)
{
    auto &transform = entity->getComponent<TransformComponent>();
    auto &entityCol = entity->getComponent<ColliderComponent>().collider;
    SDL_Rect r1 = {
        entityCol.x + static_cast<int>(transform.velocity.x * transform.speed),
        entityCol.y + static_cast<int>(transform.velocity.y * transform.speed),
        entityCol.w,
        entityCol.h};

    // Vector2D wallCenter = Vector2D(wallCol.x + wallCol.w / 2, wallCol.y + wallCol.h / 2);
    // Vector2D playerCenter = Vector2D(entityCol.x + entityCol.w / 2, entityCol.y + entityCol.h / 2);
    // transform.willCollideX = true;
    // transform.willCollideY = true;
    SDL_Rect intersection;
    if (Collision::AABB(r1, wallCol))
    {

        if (SDL_IntersectRect(&r1, &wallCol, &intersection))
        {
            if (intersection.w < intersection.h)
            {
                if (intersection.x < entityCol.x)
                {
                    transform.willCollideX = true;
                    transform.velocity.x = 0;
                    transform.expectedPos.x = transform.pos.x;
                }
                else
                {
                    transform.willCollideX = true;
                    transform.velocity.x = 0;
                    transform.expectedPos.x = transform.pos.x;
                }
            }
            else
            {
                if (intersection.y < entityCol.y)
                {

                    transform.willCollideY = true;
                    transform.velocity.y = 0;
                    transform.expectedPos.y = transform.pos.y;
                }
                else
                {
                    if (entity->hasComponent<GravityComponent>())
                    {
                        entity->getComponent<GravityComponent>().grounded = true;
                    }
                    transform.willCollideY = true;
                    transform.velocity.y = 0;
                    transform.expectedPos.y = transform.pos.y;
                }
            }
        }
    }
}