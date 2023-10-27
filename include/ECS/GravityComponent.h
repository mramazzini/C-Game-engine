#pragma once
class TransformComponent;

class GravityComponent : public Component
{
public:
    bool grounded = false;
    GravityComponent()
    {
    }
    ~GravityComponent(){};

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        if (entity->hasComponent<TransformComponent>())
        {
            if (transform->velocity.y < 3)
            {
                transform->acceleration.y += 0.1;
            }
        }
    }

private:
    TransformComponent *transform;
};