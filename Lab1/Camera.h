#pragma once
#include <Windows.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera()
	{
		this->m_moveSpeed = 5.0f;
		this->m_turnSpeed = 1.0f;
		this->m_pitchEnabled = false;
	}

	void Update(float dt);

	void initCamera(const glm::vec3& m_pos, float fov, float aspect, float nearClip, float farClip, float moveSpeed, float turnSpeed, bool pitchEnabled)
	{
		this->m_pos = m_pos;
		this->m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->m_projection = glm::perspective(fov, aspect, nearClip, farClip);

		this->m_moveSpeed = moveSpeed;
		this->m_turnSpeed = turnSpeed;
		this->m_pitchEnabled = pitchEnabled;
	}

	glm::vec3 getPos()
	{
		return this->m_pos;
	}

	inline float GetMoveSpeed() const
	{
		return this->m_moveSpeed;
	}

	inline float GetTurnSpeed() const
	{
		return this->m_turnSpeed;
	}

	inline glm::mat4 getViewProjection() const
	{
		return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	inline glm::mat4 GetProjectionMatrix() const
	{
		return this->m_projection;
	}

	inline glm::vec3 GetForwardVec() const {
		return this->m_forward;
	}

	inline glm::mat4 GetViewMatrix() const
	{
		return glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	void setLook(glm::vec3 modelPos)
	{
		m_forward = glm::vec3(glm::normalize(modelPos - m_pos));
	}

	void MoveForward(float amt)
	{
		m_pos += m_forward * amt;
	}

	void MoveRight(float amt)
	{
		m_pos += glm::cross(m_up, m_forward) * amt;
	}

	// For some reason the code between Yaw and Pitch does the opposite...
	// Instead of reworking them, I simply changed the names. I understand
	// that the name of each of these methods does not match the content,
	// but the end result does. This saves time, sanity and solves this problem.
	/*void YawRelative(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));

		m_forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(m_forward, 0.0)));
		m_up = glm::normalize(glm::cross(m_forward, right));
	}*/

	// TODO rotate on Z axis opposite of pitch angle to ensure
	// angle to ground is always perpendicular

	void YawFixed(float angle)
	{
		glm::vec3 projectedUp = glm::normalize(m_up);

		glm::vec3 yawAxis = glm::normalize(glm::cross(glm::cross(m_forward, projectedUp), m_forward));

		m_forward = glm::vec3(glm::normalize(glm::rotate(angle, yawAxis) * glm::vec4(m_forward, 0.0)));

		glm::vec3 right = glm::normalize(glm::cross(projectedUp, m_forward));
		m_up = glm::normalize(glm::cross(m_forward, right));
	}

	void Pitch(float angle)
	{
		if (m_pitchEnabled)
		{
			m_forward = glm::vec3(glm::normalize(glm::rotate(angle, m_up) * glm::vec4(m_forward, 0.0)));
			glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));

			m_up = glm::normalize(glm::cross(m_forward, right));
		}
	}

	void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
		m_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_up, 0.0)));
	}

private:
	glm::mat4 m_projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	float m_moveSpeed;
	float m_turnSpeed;
	bool m_pitchEnabled;
};


