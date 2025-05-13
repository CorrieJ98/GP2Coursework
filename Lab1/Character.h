#pragma once
#include <vector>

#include "GameObject.h"

class Character : GameObject{
public:
	Character() : m_moveable(true), m_health(1), m_damage(1), m_moveSpeed(5.0f) {};
	Character(bool moveable, int health, int damage, float moveSpeed, bool state)
	{
		this->m_moveable = moveable;
		this->m_health = health;
		this->m_damage = damage;
		this->m_moveSpeed = moveSpeed;
		this->state = state;
		this->m_characterName = "UNNAMED";
	};

	int GetHealth() { return this->m_health; }
	int GetDamage() { return this->m_damage; }
	float GetMoveSpeed() { return this->m_moveSpeed; }

	void SetHealth(int health) { this->m_health = health; }
	void SetDamage(int damage) { this->m_damage = damage; }
	void SetMoveSpeed(float moveSpeed) { this->m_moveSpeed = moveSpeed; }

private:

	void ToggleMoveable() { this->m_moveable = !this->m_moveable; }
	void Die() { this->state = false; this->m_moveable = false;  this->transform.SetPos(glm::vec3(-10, -10, -10)); };
	
	std::string m_characterName;
	glm::vec3 m_centreMass;
	glm::vec3 m_attackOrigin;
	int m_health;
	int m_damage;
	bool m_moveable;
	float m_moveSpeed;


};
