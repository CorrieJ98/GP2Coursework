#include "Camera.h"

void Camera::Update(float dt)
{
	// TODO currently diagonal movement has the root2 problem
	// how to normalise velocity??

#pragma region Keybindings
	// W
	if (GetKeyState(0x57) & 0x8000)
	{
		MoveForward(GetCamMoveSpeed() * dt);
	}

	// S
	if (GetKeyState(0x53) & 0x8000)
	{
		MoveForward(-GetCamMoveSpeed() * dt);
	}

	// A
	if (GetKeyState(0x41) & 0x8000)
	{
		MoveRight(GetCamMoveSpeed() * dt);
	}

	// D
	if (GetKeyState(0x44) & 0x8000)
	{
		MoveRight(-GetCamMoveSpeed() * dt);
	}

	// Right Arrow
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		YawFixed(-GetCamTurnSpeed() * dt);
	}

	// Left Arrow
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		YawFixed(GetCamTurnSpeed() * dt);
	}


	// TODO pitch modifies the Yaw axis, meaning the camera X axis can Roll
	// off of the horizon...not sure how to fix this at all, disabling Pitch for now.

	/*
	// Up Arrow
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Pitch(-GetCamTurnSpeed() * dt);
	}

	// Down Arrow
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Pitch(GetCamTurnSpeed() * dt);
	}
	*/

#pragma endregion
}
