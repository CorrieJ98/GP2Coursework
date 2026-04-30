#include "Camera.h"

void Camera::Update(float dt)
{
	// TODO currently diagonal movement has the root2 problem

    if (GetCamMoveSpeed() > m_moveSpeed) {
        m_moveSpeed *= ONE_ROOT2;
    }

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
		Yaw(-GetCamTurnSpeed() * dt);
	}

	// Left Arrow
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		Yaw(GetCamTurnSpeed() * dt);
	}

	 //Up Arrow
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Pitch(-GetCamTurnSpeed() * dt);
	}

	 //Down Arrow
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Pitch(GetCamTurnSpeed() * dt);
	}
	

#pragma endregion
}
