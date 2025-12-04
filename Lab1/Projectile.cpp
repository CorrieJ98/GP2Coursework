#include "Projectile.h"

void Projectile::Launch(glm::vec3 origin, glm::vec3 target)
{
    this->transform.SetPos(origin);
    this->SetState(true);
    velocity = glm::normalize(target) * speed;
    aliveTime = 0.0f;
}

void Projectile::Update(float dt)
{
    if (state) {
        transform.SetPos(transform.GetPos() + velocity * dt);
        aliveTime += dt;
        if (aliveTime >= lifetime) {
            this->SetState(false);
        }
    }
}
