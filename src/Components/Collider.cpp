#include "ECS/Components/Collider.h"
#include "ECS/Components/Transform.h"

extern Coordinator gCoordinator;
Collider::Collider()
{
}
Collider::Collider(std::string t, Entity &mEntity)
{
    entity = mEntity;
    tag = t;
    setCollider();
    transform = &gCoordinator.GetComponent<Transform>(entity);
}

Collider::Collider(std::string t, int xpos, int ypos, int size, Entity &mEntity)
{
    entity = mEntity;
    tag = t;
    collider.x = xpos;
    collider.y = ypos;
    collider.h = collider.w = size;
}

void Collider::update()
{

    if (tag != "terrain")
    {
        collider.x = static_cast<int>(transform->pos.x) + hitbox.x * transform->scale;
        collider.y = static_cast<int>(transform->pos.y) + hitbox.y * transform->scale;
        collider.w = desR.w = hitbox.w * transform->scale;
        collider.h = desR.h = hitbox.h * transform->scale;
    }

    desR.x = collider.x - Game::camera.x;
    desR.y = collider.y - Game::camera.y;
}

void Collider::draw()
{

    //  /std::cout << desR.x << " " << desR.y << " " << desR.w << " " << desR.h << std::endl;
    TextureManager::Draw(Game::assets->getTexture("collider"), srcR, desR, SDL_FLIP_NONE);
}

void Collider::setCollider()
{
    collider = hitbox = *(Game::hitboxes->getHitbox(tag));
}