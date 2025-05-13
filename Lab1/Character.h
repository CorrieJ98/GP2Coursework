#pragma once
#include "GameObject.h"

class Character : GameObject{
public:
	Character() : m_moveable(true), m_health(1), m_damage(1), m_moveSpeed(5.0f) {};
	Character(bool moveable, int health, int damage, float moveSpeed);

	int GetHealth() { return this->m_health; }
	int GetDamage() { return this->m_damage; }
	float GetMoveSpeed() { return this->m_moveSpeed; }

	void SetHealth(int health) { this->m_health = health; }
	void SetDamage(int damage) { this->m_damage = damage; }
	void SetMoveSpeed(float moveSpeed) { this->m_moveSpeed = moveSpeed; }
	void ToggleMoveable() { this->m_moveable = !this->m_moveable; }

private:

	void Die() { this->state = false; };
	
	int m_health;
	int m_damage;
	bool m_moveable;
	float m_moveSpeed;
};
