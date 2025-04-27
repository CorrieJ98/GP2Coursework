#pragma once
#include <iostream>
#include <functional>
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <chrono>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void linkFogShader();
	void linkToon();
	void linkRimShader();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void UpdateDeltaTime();

	//void playAudio(unsigned int Source, glm::vec3 pos);

	Display _gameDisplay;
	GameState _gameState;
	Mesh monkeyMesh;
	Mesh ballMesh;
	Camera cam;
	Shader fogShader;
	Shader toonShader;
	Shader rimShader;

	Texture waterTexture;
	
	//Audio audioDevice;

	float counter;
	std::chrono::high_resolution_clock::time_point lastFrameTime;
	float deltaTime;

	unsigned int whistle;
	unsigned int backGroundMusic;
};

