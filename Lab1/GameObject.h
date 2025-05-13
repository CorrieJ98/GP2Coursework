#pragma once
#include <iostream>
#include <functional>
#include "Mesh.h"
#include "transform.h"
#include "Shader.h"
#include "Texture.h"

struct Layer {
	Layer()
	{
		this->collision = 1;
		this->interactable = 1;
	};

	Layer(uint8_t _collision, uint8_t _interactable) {
		this->collision = _collision;
		this->interactable = _interactable;
	};

	uint8_t collision;		// what can this collide with?	0-255
	uint8_t interactable;	// what can this interact with?	0-255
};

struct GameObject {

	GameObject() : transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)), layer(0, 0), state(false){}

	GameObject(Mesh& _mesh, Shader& _shader, Texture& _texture) : transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)), layer(0, 0), state(false) {
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

	Transform transform;
	Mesh mesh;
	Shader shader;
	Texture texture;
	Layer layer;
	bool state;
};

// TODO, enable and disable states, get something shooting a fireball!!!