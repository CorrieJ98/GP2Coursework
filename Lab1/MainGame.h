#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <chrono>
#include "Audio.h"
#include "Camera.h"
#include "CharacterList.h"
#include "Display.h" 
#include "GameClock.h"
#include "SkyBox.h"

enum class GameState{PLAY, EXIT};

#define DESIRED_FPS 60

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
	void linkExplosionShader(GameObject& gameObject);
	void linkSunShader(GameObject& gameObject);
	void linkEmapping(GameObject& gameObject);
    void linkADSLighting(GameObject& gameObject);
	

	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void InitGameObjects();
	void UpdateAllGameObjects(float dt);
	void UpdateGameObject(GameObject& gO, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::function<void(GameObject&)> linkerMethod, bool useIndices);
	

	//void playAudio(unsigned int Source, glm::vec3 pos);

    gc::dt& deltaTime = gc::dt::Instance(); // singleton
    gc::counter& counter = gc::counter::Instance(); // singleton

	Display _gameDisplay;
	GameState _gameState;
	Player player;
	//Camera cam;
	
	Mesh monkeyMesh;
	Mesh ballMesh;
	Mesh planeMesh;
	Mesh capsuleMesh;

	Shader fogShader;
	Shader toonShader;
	Shader rimShader;
	Shader explosionShader;
	Shader sunShader;
	Shader eMapping;
    Shader adsLighting;

	Texture waterTexture;
	Texture brickWallTexture;
	Texture brickGroundTexture;
	Texture redDustTexture;

    Skybox skybox;
	
	//Audio audioDevice;

	GameObject monkey;
	GameObject ball;
	GameObject plane;

	Projectile fireball;

	CasterNPC casterNPC;

	unsigned int whistle;
	unsigned int backGroundMusic;
};

