#pragma once
#include <iostream>
#include <functional>
#include <string>
#include "Mesh.h"
#include "transform.h"
#include "Shader.h"
#include "Texture.h"

struct Layer {
	Layer()
	{
		this->collision = 1;
		this->interactable = 1;
		this->team = 0;
	};

	Layer(uint8_t _collision, uint8_t _interactable, uint8_t _team) {
		this->collision = _collision;
		this->interactable = _interactable;
		this->team = _team;
	};

	uint8_t collision;		// what can this collide with?	0-255
	uint8_t interactable;	// what can this interact with?	0-255
	uint8_t team;			// what team is this object on? 0-255
};

class GameObject {
public:
	GameObject() : transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)), layer(1,1,0), state(false){}

	GameObject(Mesh& _mesh, Shader& _shader, Texture& _texture) : transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)), layer(0, 0, 0), state(false) {
		this->mesh = _mesh;
		this->shader = _shader;
		this->texture = _texture;
	}

	~GameObject() {
		this->texture.~Texture();
		this->shader.~Shader();
		this->mesh.~Mesh();
	}

	void init(Mesh& _mesh, Shader& _shader, Texture& _texture, bool _state) {
		this->mesh = _mesh;
		this->shader = _shader;
		this->texture = _texture;
		this->state = _state;
	}

	// Note: I tried overloading but VS really wasn't a fan.
	// as far as I am aware this is a totally legal operation,
	// although I am not experienced enough to argue with the
	// debugger or the compiler.
	/*
	virtual void Update() { std::cout << "ERROR: Update() called from base" << std::endl; }
	virtual void Update(float dt) { std::cout << "ERROR: Update(float dt) called from base" << std::endl; }
	*/

	virtual void Update() { std::cout << "ERROR: Update() called from base" << std::endl; }
	virtual void UpdateDT(float dt) { std::cout << "ERROR: Update(float dt) called from base" << std::endl; }

	void ToggleState() { this->state = !this->state; }

	glm::vec3 GetDirectionTowards(glm::vec3& from, glm::vec3& to) {
		glm::vec3 delta = to - from;
		if (glm::length(delta) < 0.0001f) // avoid division by zero
			return glm::vec3(0.0f);
		return glm::normalize(delta);	// direction return a unit vector of length 1
	}

	void MoveTo(glm::vec3 point, float moveSpeed, float dt);

	Transform transform;
	Mesh mesh;
	Shader shader;
	Texture texture;
	Layer layer;
	float radius;
	bool state;
};

