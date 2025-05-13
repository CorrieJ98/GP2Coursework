#include "Camera.h"

void Camera::Update(float dt)
{
	// TODO currently diagonal movement has the root2 problem
	// how to normalise velocity??

#pragma region Keybindings
	// W
	if (GetKeyState(0x57) & 0x8000)
	{
		MoveForward(GetMoveSpeed() * dt);
	}

	// S
	if (GetKeyState(0x53) & 0x8000)
	{
		MoveForward(-GetMoveSpeed() * dt);
	}

	// A
	if (GetKeyState(0x41) & 0x8000)
	{
		MoveRight(GetMoveSpeed() * dt);
	}

	// D
	if (GetKeyState(0x44) & 0x8000)
	{
		MoveRight(-GetMoveSpeed() * dt);
	}

	// Right Arrow
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		YawFixed(-GetTurnSpeed() * dt);
	}

	// Left Arrow
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		YawFixed(GetTurnSpeed() * dt);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		// jump in here??
	}

	// TODO pitch modifies the Yaw axis, meaning the camera X axis can Roll
	// off of the horizon...not sure how to fix this at all, disabling Pitch for now.

	/*
	// Up Arrow
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Pitch(-GetTurnSpeed() * dt);
	}

	// Down Arrow
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Pitch(GetTurnSpeed() * dt);
	}
	*/

#pragma endregion
}
