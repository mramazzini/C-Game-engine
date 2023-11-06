#include "Components/Projectile.h"
#include "Utils/Vector2D.h"
#include "Components/Transform.h"
#include "Managers/CameraManager.h"
#include "Game.h"
extern Coordinator gCoordinator;

Projectile::Projectile() {}
Projectile::Projectile(int mrange, int mspeed, Vector2D vector, Entity mEntity)
{
    velocity = vector;
    distance = 0;
    range = mrange;
    speed = mspeed;
    entity = mEntity;
    transform = &gCoordinator.GetComponent<Transform>(entity);
    transform->velocity = velocity;
}
Projectile::~Projectile(){};

void Projectile::update()
{
    distance += speed;
    // std::cout << transform->pos << std::endl;
    // destroy projectile if exceeding its max range
    if (distance > range)
    {
        active = false;
        // std::cout << "out of range" << std::endl;
    }
    else if ( // destroy projectile if out of bounds
        transform->pos.x > Game::camera->getCamera().x + Game::camera->getCamera().w ||
        transform->pos.x < Game::camera->getCamera().x ||
        transform->pos.y > Game::camera->getCamera().y + Game::camera->getCamera().h ||
        transform->pos.y < Game::camera->getCamera().y)
    {
        // std::cout << "out of bounds" << std::endl;
        active = false;
    }
}