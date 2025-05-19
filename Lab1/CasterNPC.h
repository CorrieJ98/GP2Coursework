#pragma once
#include "Character.h"
#include "Player.h"

class CasterNPC : public Character {
public:
    CasterNPC() : onCD(true), abilityCooldown(3.0f), currentCooldown(0.0f), patrolForward(true) {}

    void SetPatrolPoints(glm::vec3 pointA, glm::vec3 pointB) {
        patrolPointA = pointA;
        patrolPointB = pointB;
    }

    void UpdateDT(float dt) override;

private:
    void Patrol(float dt);
    void CastFireball();

    bool onCD;
    float abilityCooldown;
    float currentCooldown;

    glm::vec3 patrolPointA;
    glm::vec3 patrolPointB;
    bool patrolForward;
};
