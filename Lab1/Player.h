#pragma once
#include "Character.h"
#include "Camera.h"

class Player : public Camera, public Character {
public:
	void Update(float dt);
	void ParseInputs(float dt);
	void SyncTransformWithCam();

private:

};