#pragma once
#include "Character.h"
#include "Player.h"

class CasterNPC : public Character {
public:
    CasterNPC() : canShoot(true), abilityCooldown(3.0f), currentCooldown(0.0f), patrolForward(true) {}

    void SetPatrolPoints(glm::vec3 pointA, glm::vec3 pointB) {
        patrolPointA = pointA;
        patrolPointB = pointB;
    }

    void UpdateDT(float dt) override;

    void SetCurrentCD(float cd) { this->currentCooldown = cd; }
    void SetAbilityCD(float cd) { this->abilityCooldown = cd; }
    float GetCurrentCD() { return this->currentCooldown; }
    float GetAbilityCD() { return this->abilityCooldown; }


private:
    void Patrol(float dt);
    void CastFireball(glm::vec3 targetPos);
    void CooldownLoop(float dt);

    bool canShoot;
    float abilityCooldown;
    float currentCooldown;

    glm::vec3 patrolPointA;
    glm::vec3 patrolPointB;
    bool patrolForward;
};
