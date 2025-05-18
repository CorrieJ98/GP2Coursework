#pragma once
#include "Character.h"
#include "Player.h"

class CasterNPC : public Character {
public:
	void Update() override;

	void CastFireball() {

	}

private:
	bool onCD;
	float abilityCooldown;
};