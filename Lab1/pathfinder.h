#pragma once
#include "character.h"

class Pathfinder {

public:

private:
	void AddWaypoint(glm::vec3 wp) { this->m_route.push_back(wp); }
	void RemoveWaypointAtIndex(int index) { this->m_route.erase(m_route.begin() + index); }
	std::vector<glm::vec3> m_route;
};