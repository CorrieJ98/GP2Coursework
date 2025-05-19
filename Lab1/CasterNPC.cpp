#include "CasterNPC.h"

void CasterNPC::UpdateDT(float dt)
{
	SetMoveable(true);
	Patrol(dt);
	CooldownLoop(dt);

	//std::cout << "currentCD: " << currentCooldown << std::endl;
	//std::cout << "abilityCD: " << abilityCooldown << std::endl;

	// attack condition
	if (canShoot) {
		CastFireball(glm::vec3(0,0,0));	// send the fireball to the origin for now
		canShoot = false;
		CooldownLoop(dt);
	}
}


void CasterNPC::Patrol(float dt) {
	glm::vec3 target = patrolForward ? patrolPointB : patrolPointA;
	MoveTo(target, GetMoveSpeed(), dt);

	float distance = glm::length(transform.GetPos() - target);
	//std::cout << distance << std::endl;
	if (distance < 0.1f) {
		patrolForward = !patrolForward;  // Switch direction
		//std::cout << "patrolForward switched" << '\n';
	}
}

void CasterNPC::CastFireball(glm::vec3 targetPos) {
		std::cout << "CastFireball() called from CasterNPC" << '\n';
		glm::vec3 forward = glm::rotate(glm::mat4(1.0f), glm::radians(transform.GetRot().y), glm::vec3(0, 1, 0)) * glm::vec4(0, 0, 1, 0);
		glm::vec3 direction = glm::normalize(targetPos - this->transform.GetPos());
		GetProjectileObj().Launch(GetAttackOrigin(), direction);
}

void CasterNPC::CooldownLoop(float dt)
{
	if (!canShoot) {
		SetCurrentCD(GetCurrentCD() + dt);

		if (GetCurrentCD() >= GetAbilityCD()) {
			canShoot = true;
			SetCurrentCD(0.0f);
		}
	}
}
