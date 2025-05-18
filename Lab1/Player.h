#pragma once
#include "Character.h"
#include "Camera.h"

class Player : public Camera, public Character {
public:
	void Update(float dt);

private:
	void SyncTransformWithCam();
	void ParseInputs(float dt);
};