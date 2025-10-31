#pragma once

constexpr auto ROOT2 = 1.41421356237f;

class AABB {
public:

	AABB()
	{
		this->botRight = glm::vec2(0.5f, 0.5f);
		this->topLeft = glm::vec2(-0.5f, -0.5f);
	};

	AABB(const glm::vec2& _botRight, const glm::vec2& _topLeft)
	{
		this->botRight = _botRight;
		this->topLeft = _topLeft;
	};

	glm::vec2 botRight;
	glm::vec2 topLeft;

	void GetBoundsFromRadius(glm::vec2 origin_in, float radius_in, glm::vec2& topLeft_out, glm::vec2& botRight_out)
	{
		float diagLength = radius_in * ROOT2;

		// https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
	}

	
private:
};

//// <summary> botRight and topLeft are 1:sqrt(2) ratio </summary>