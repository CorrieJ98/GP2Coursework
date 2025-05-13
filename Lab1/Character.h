#pragma once
#include "GameObject.h"

class Character : GameObject{
public:
	Character() {};

	int GetHealth() { return this->health; }
	int GetDamage() { return this->damage; }
	float GetMoveSpeed() { return this->moveSpeed; }

	void SetHealth(int hp) { this->health = hp; }
	void SetDamage(int dmg) { this->damage = dmg; }
	void SetMoveSpeed(float ms) { this->moveSpeed = ms; }

private:

	void Die() { this->state = false; };

	int health;
	int damage;
	float moveSpeed;
};
