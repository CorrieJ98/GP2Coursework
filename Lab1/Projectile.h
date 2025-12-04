#pragma once
#include "GameObject.h"
#include "GameClock.h"

class Projectile : public GameObject {
public:
    Projectile() : velocity(glm::vec3(0.0f)), lifetime(100.0f), aliveTime(0.0f), damage(1), speed(3.0f) {}


    void SetDamage(int dmg) { damage = dmg; }
    int GetDamage() const { return damage; }

    void Launch(glm::vec3 origin, glm::vec3 target);
    void Update(float dt);

private:
    glm::vec3 velocity;
    float speed;
    float maxSpeed;
    float lifetime;
    float aliveTime;
    int damage;
};
