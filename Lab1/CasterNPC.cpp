#include "CasterNPC.h"

void CasterNPC::UpdateDT(float dt) {
    Patrol(dt);

    // Cooldown logic
    if (onCD) {
        currentCooldown -= dt;
        if (currentCooldown <= 0.0f) {
            onCD = false;
            currentCooldown = 0.0f;
        }
    }

    // Simulate attack condition (e.g., player in range, etc.)
    if (!onCD /* && some condition */) {
        CastFireball();
        onCD = true;
        currentCooldown = abilityCooldown;
    }
}


void CasterNPC::Patrol(float dt)
{
}

void CasterNPC::CastFireball() {
    if (GetProjectileObj().state) {
        glm::vec3 forward = glm::rotate(glm::mat4(1.0f), glm::radians(transform.GetRot().y), glm::vec3(0, 1, 0)) * glm::vec4(0, 0, 1, 0);
        glm::vec3 direction = glm::normalize(glm::vec3(forward));
        GetProjectileObj().Launch(GetAttackOrigin(), direction);
    }
}
