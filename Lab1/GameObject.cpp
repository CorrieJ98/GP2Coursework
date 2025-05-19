#include "GameObject.h"

void GameObject::MoveTo(glm::vec3 targetPoint, float moveSpeed, float dt) {
    glm::vec3 currentPos = this->transform.GetPos();
    glm::vec3 direction = targetPoint - currentPos;
    float distance = glm::length(direction);

    if (distance < 0.0001f)
        return;

    glm::vec3 directionNormalized = glm::normalize(direction);
    float moveStep = moveSpeed * dt;

    glm::vec3 newPos;
    if (moveStep >= distance) {
        newPos = targetPoint;
    }
    else {
        newPos = currentPos + directionNormalized * moveStep;
    }

    this->transform.SetPos(newPos);
}
