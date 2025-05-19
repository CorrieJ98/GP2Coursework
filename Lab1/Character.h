#pragma once
#include <vector>
#include "Projectile.h"
#include "GameObject.h"


class Character : public GameObject{
public:
	Character() : m_moveable(true), m_health(1), m_damage(1), m_moveSpeed(5.0f), m_projectile(Projectile()) {};
	Character(bool moveable, int health, int damage, float moveSpeed, bool state, Projectile projectile)
	{
		this->m_moveable = moveable;
		this->m_health = health;
		this->m_damage = damage;
		this->m_moveSpeed = moveSpeed;
		this->state = state;
		this->m_characterName = "UNNAMED";
		this->m_projectile = projectile;
		this->m_projectile.state = false;
	};

	int GetHealth() { return this->m_health; }
	int GetDamage() { return this->m_damage; }
	float GetMoveSpeed() { return this->m_moveSpeed; }
	Projectile GetProjectileObj() { return this->m_projectile; }
	glm::vec3 GetAttackOrigin() { return this->m_attackOrigin; }
	glm::vec3 GetCoM() { return this->m_centreMass; }
	std::string GetName() { return this->m_characterName; }
	
	void SetProjectile(Projectile proj) { this->m_projectile = proj; }
	void SetHealth(int health) { this->m_health = health; }
	void SetDamage(int damage) { this->m_damage = damage; }
	void SetMoveSpeed(float moveSpeed) { this->m_moveSpeed = moveSpeed; }
	void SetAttackOrigin(glm::vec3 attackOrigin) { this->m_attackOrigin = attackOrigin; }
	void SetCoM(glm::vec3 centreMass) { this->m_centreMass = centreMass; }
	void SetName(std::string characterName) { this->m_characterName = characterName; }
	void SetMoveable(bool moveable) { this->m_moveable = moveable; }

	void Die() { this->state = false; this->m_moveable = false;  this->transform.SetPos(glm::vec3(-10, -10, -10)); };

	virtual void InitCharacter(bool moveable, int health, int damage, float moveSpeed, bool state, Projectile projectile, std::string name) {
		this->m_moveable = moveable;
		this->m_health = health;
		this->m_damage = damage;
		this->m_moveSpeed = moveSpeed;
		this->state = state;
		this->m_characterName = name;
		this->m_projectile = projectile;
		this->m_projectile.state = false;
	}

private:
	std::string m_characterName;
	glm::vec3 m_centreMass;
	glm::vec3 m_attackOrigin;
	Projectile m_projectile;
	int m_health;
	int m_damage;
	bool m_moveable;
	float m_moveSpeed;


};
