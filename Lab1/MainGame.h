#pragma once
#include "Audio.h"
#include "Camera.h"
#include "CharacterList.h"
#include "Display.h" 
#include "DLLManager.h"
#include "GameClock.h"
#include "ShaderManager.h"
#include "SkyBox.h"
#include <chrono>
#include <functional>
#include <GL/glew.h>
#include <iostream>
#include <SDL\SDL.h>
#include <string>

#define DESIRED_FPS 60

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

    void testDLLManager();


    void SetActiveShader(const Shader& shader);
    void ApplyActiveShader();

	void linkFogShader(GameObject& gameObject);
	void linkToonShader(GameObject& gameObject);
	void linkRimShader(GameObject& gameObject);
	void linkExplosionShader(GameObject& gameObject);
	void linkSunShader(GameObject& gameObject);
	void linkEmapping(GameObject& gameObject);
    void linkADSLighting(GameObject& gameObject);
    void linkFireballShader(GameObject& gameObject);

	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void InitGameObjects();
	void UpdateAllGameObjects(float dt);
	void UpdateGameObject(GameObject& gO, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::function<void(GameObject&)> linkerMethod, bool useIndices);
	

	//void playAudio(unsigned int Source, glm::vec3 pos);

    gc::dt& deltaTime = gc::dt::Instance(); // singleton
    gc::counter& counter = gc::counter::Instance(); // singleton

	Display _gameDisplay;
	GameState _gameState;
	Player player;  // inherits from Camera
	
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
    Shader fireballShader;

	Texture waterTexture;
	Texture brickWallTexture;
	Texture brickGroundTexture;
	Texture redDustTexture;
    Texture noiseTexture;

    Skybox skybox;
	
	GameObject monkey;
	GameObject sun;
    GameObject ball;
	GameObject plane;

	Projectile fireball;

	CasterNPC casterNPC;

	unsigned int whistle;
	unsigned int backGroundMusic;
};

