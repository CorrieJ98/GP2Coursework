#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
public:
    Projectile() : velocity(glm::vec3(0.0f)), lifetime(10.0f), aliveTime(0.0f), damage(1), speed(3.0f) {}

    void UpdateDT(float dt) override {
        if (!state) 
            return;

        // Move forward
        glm::vec3 newPos = transform.GetPos() + velocity * speed * dt;
        transform.SetPos(newPos);

        // Track lifespan
        aliveTime += dt;
        if (aliveTime >= lifetime) {
            this->SetState(false);
            aliveTime = 0.0f;
            transform.SetPos(glm::vec3(-666, -666, -666)); // send to purgatory (just move it offscreen)
        }
    }

    void Launch(glm::vec3 origin, glm::vec3 dir) {
        this->transform.SetPos(origin);
        velocity = glm::normalize(dir) * speed;
        aliveTime = 0.0f;
        this->SetState(true);
    }

    void SetDamage(int dmg) { damage = dmg; }
    int GetDamage() const { return damage; }
private:
    glm::vec3 velocity;
    float speed;
    float lifetime;
    float aliveTime;
    int damage;
};
