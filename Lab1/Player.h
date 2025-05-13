#pragma once
#include "Character.h"
#include "Camera.h"

class Player : Character {

public:


private:
	void SlaveCameraFirstPerson();
	void SlaveCameraThirdPerson();
	void IsolateCamera();

	void Update();


};