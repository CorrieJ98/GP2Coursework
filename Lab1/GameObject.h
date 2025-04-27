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

	uint8_t collision;		// what can this collide with?
	uint8_t interactable;	// what can this interact with?
};

struct GameObject {

	GameObject() : transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)), layer(0, 0) {}

	GameObject(std::string mesh_filepath, std::string shader_filepath, std::string texture_filepath) : transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)) {};

	GameObject(Transform& _transform, Mesh& _mesh, Shader& _shader, Texture& _texture, Layer& _layer) {
		this->transform = _transform;
		this->mesh = _mesh;
		this->shader = _shader;
		this->texture = _texture;
		this->layer = _layer;
	}

	~GameObject() {
		// TODO cleanup in here
	}

	inline void SetRadius(float r) { this->radius = r; }
	inline float GetRadius() { return this->radius; }

	void init() {
		mesh.updateSphereData(*transform.GetPos(), this->radius);
	}

	Transform transform;
	Mesh mesh;
	Shader shader;
	Texture texture;
	Layer layer;
	float radius;
};