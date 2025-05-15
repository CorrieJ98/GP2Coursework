#pragma once
#include <iostream>
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

struct GameObject {

	GameObject() : transform(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1)), layer(1, 1, 0), state(false) {}

	void init(std::shared_ptr<Mesh> _mesh, std::shared_ptr<Shader> _shader, std::shared_ptr<Texture> _texture, bool _state) {
		this->state = _state;
		this->transform.SetPos(glm::vec3(0, 0, 0));
		this->transform.SetRot(glm::vec3(0, 0, 0));
		this->transform.SetScale(glm::vec3(1, 1, 1));
		this->mesh = _mesh;
		this->shader = _shader;
		this->texture = _texture;
	}

	virtual void Update() {
		std::cout << "ERROR: `Update()` called from GameObject: please override" << std::endl;
	}

	void ToggleState() { this->state = !this->state; }

	Transform transform;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	Layer layer;
	bool state;
};

