#pragma once
#include <glm/glm.hpp>
#include "transform.h"

constexpr float ROOT2 = 1.41421356237f;
/*
    The AABB is computed as a square that fully contains a circle of radius R
      ⇒ halfExtents = R * sqrt(2)
*/

class AABB {
public:
    AABB() = default;

    // Construct directly from a GameObject
    AABB(const Transform& parentTransform, float radius) {
        init(parentTransform, radius);
    }

    // Initialize from GameObject (Transform + radius)
    void init(const Transform& parentTransform, float radius) {
        this->parentTransform = parentTransform;
        this->radius = radius;

        float half = radius * ROOT2;   // square that encloses the circle
        halfExtents = glm::vec2(half, half);

        update(); // compute botRight/topLeft once
    }

    // Call every frame to sync with parent transform
    void update() {
        glm::vec2 center(parentTransform.GetPos().x, parentTransform.GetPos().y);

        topLeft = center - halfExtents;
        botRight = center + halfExtents;
    }

    glm::vec2 GetCenter() const {
        return (topLeft + botRight) * 0.5f;
    }

    glm::vec2 GetTopLeft() const { return topLeft; }
    glm::vec2 GetBottomRight() const { return botRight; }

private:
    float radius = 1.0f;
    glm::vec2 halfExtents;  // ±(radius * sqrt(2))

    glm::vec2 topLeft;
    glm::vec2 botRight;

    Transform parentTransform;
};

/*

HOW TO USE:


class GameObject {
public:
    Mesh mesh;
    Shader shader;
    Transform transform;
    float radius;

    AABB aabb;

    GameObject(float radius)
        : radius(radius)
    {
        aabb.init(transform, radius);
    }

    void Update() {
        transform.Update(); // whatever you already do
        aabb.update();
    }
};
*/