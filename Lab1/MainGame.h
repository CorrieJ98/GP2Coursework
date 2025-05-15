#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <chrono>
#include "Assets.h"
#include "Audio.h"
#include "Camera.h"
#include "Display.h" 
#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"


enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();
private:

	void InitSystems();
	void ProcessInput();
	void GameLoop();
	void DrawGame();
	void linkFogShader(GameObject& gameObject);
	void linkToonShader(GameObject& gameObject);
	void linkRimShader(GameObject& gameObject);
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void UpdateDeltaTime();
	void InitGameObjects();
	void UpdateAllGameObjects();
	void UpdateGameObject(GameObject& gO, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::function<void(GameObject&)> linkerMethod, bool useIndices);

	//void playAudio(unsigned int Source, glm::vec3 pos);

	Display _gameDisplay;
	GameState _gameState;
	Camera cam;

	//Mesh monkeyMesh;
	//Mesh ballMesh;
	//Mesh planeMesh;
	//Mesh capsuleMesh;

	//Shader fogShader;
	//Shader toonShader;
	//Shader rimShader;

	//Texture waterTexture;
	//Texture brickWallTexture;
	//Texture brickGroundTexture;
	
	GameObject monkey;
	GameObject ball;
	GameObject plane;
	GameObject capsule;

	float counter;
	std::chrono::high_resolution_clock::time_point lastFrameTime;
	float deltaTime;

	unsigned int whistle;
	unsigned int backGroundMusic;
};

