#include "MainGame.h"


//Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::Run()
{
	InitSystems();
	GameLoop();
}

void MainGame::InitSystems()
{
	_gameDisplay.initDisplay();
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	//backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");

	// now handled in Assets.cpp
	//planeMesh.loadModel("..\\res\\surface.obj");
	//monkeyMesh.loadModel("..\\res\\monkey3.obj");
	//ballMesh.loadModel("..\\res\\Ball.obj");
	//fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag"); //new shader
	//toonShader.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //new shader
	//rimShader.init("..\\res\\Rim.vert", "..\\res\\Rim.frag");
	//waterTexture.load("..\\res\\water.jpg"); //load texture
	//brickWallTexture.load("..\\res\\brickwall.jpg");
	//brickGroundTexture.load("..\\res\\bricks.jpg");

	cam.initCamera(glm::vec3(2, 0, -4), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f, 4.0f, 1.5f, false);

	InitGameObjects();

	counter = 1.0f;
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{

		UpdateDeltaTime();
		ProcessInput();
		UpdateAllGameObjects();
		DrawGame();

		//collision(monkeyMesh.getSpherePos(), monkeyMesh.getSphereRadius(), ballMesh.getSpherePos(), ballMesh.getSphereRadius());
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;
	cam.Update(deltaTime);

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		}
	}

}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

//void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
//{
//	
//	ALint state; 
//	alGetSourcei(Source, AL_SOURCE_STATE, &state);
//	/*
//	Possible values of state
//	AL_INITIAL
//	AL_STOPPED
//	AL_PLAYING
//	AL_PAUSED
//	*/
//	if (AL_PLAYING != state)
//	{
//		audioDevice.playSound(Source, pos);
//	}
//}
void MainGame::linkRimShader(GameObject& gameObject)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	s_RimShader->setMat4("modelMatrix", gameObject.transform.GetModel());
	s_RimShader->setMat4("viewMatrix", cam.GetViewMatrix());
	s_RimShader->setFloat("rimPower", 3.0f);
	s_RimShader->setVec3("rimColor", glm::vec3(0.8f, 0.0f, 0.0f));
	s_RimShader->setVec3("camPos", cam.getPos());


	/*transform.SetPos(glm::vec3(1.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.5, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));*/


}


// TODO not displaying this shader
void MainGame::linkFogShader(GameObject& gameObject)
{
	s_FogShader->setMat4("transform", gameObject.transform.GetModel());
}

void MainGame::linkToonShader(GameObject& gameObject)
{
	s_ToonShader->setMat4("modelMatrix", gameObject.transform.GetModel());
	s_ToonShader->setMat4("transform", gameObject.transform.GetMVP(cam));
	s_ToonShader->setVec3("lightDir", glm::normalize(glm::vec3(0.0f)));
	s_ToonShader->setVec3("lightDir", glm::cross(-cam.GetForwardVec(), cam.getPos()));
}


void MainGame::UpdateDeltaTime()
{
	// potentially quite error prone and messy, but it seems to work for now.
	// 1. get the current time
	// 2. get period of time between current and last frames
	// 3. and then update the last frame time for the next cycle

	std::chrono::steady_clock::time_point currentFrameTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentFrameTime - lastFrameTime).count();
	lastFrameTime = currentFrameTime;
}

void MainGame::InitGameObjects()
{
	monkey.init(s_MonkeyMesh, s_FogShader, s_WaterTexture, true);
	ball.init(s_BallMesh, s_FogShader, s_WaterTexture, true);
	plane.init(s_PlaneMesh, s_FogShader, s_BrickGroundTexture, true);
	capsule.init(s_CapsuleMesh, s_FogShader, s_BrickGroundTexture, true);
}

void MainGame::UpdateAllGameObjects()
{
	// GameObject
	// positional modifiers
	// rotational modifiers
	// GameObject scale
	// shaders

	// monkey
	UpdateGameObject(monkey,
		glm::vec3(sin(counter += deltaTime), 0, 0),
		glm::vec3(0, counter * 0.5f, 0),
		glm::vec3(1, 1, 1),
		std::bind(&MainGame::linkFogShader, this, std::placeholders::_1),
		false);

	// ball
	UpdateGameObject(ball,
		glm::vec3(10, cos(counter += deltaTime), -2),
		glm::vec3(0, 0, -counter * 0.5f),
		glm::vec3(1, 1, 1),
		std::bind(&MainGame::linkFogShader, this, std::placeholders::_1),
		false);

	// ground plane
	UpdateGameObject(plane,
		glm::vec3(0, -15.1f, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0.1f),
		std::bind(&MainGame::linkFogShader, this, std::placeholders::_1),
		false);

	//

}

void MainGame::UpdateGameObject(GameObject& gO, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::function<void(GameObject&)> linkerMethod, bool altDrawingMethod)
{

	gO.transform.SetPos(position);
	gO.transform.SetRot(rotation);
	gO.transform.SetScale(scale);

	if (gO.state)
	{
		gO.texture->Bind(0);
		gO.shader->Bind();
		linkerMethod(gO);
		gO.shader->Update(gO.transform, cam);

		if (altDrawingMethod) {
			gO.mesh->drawVertexes();
		}
		else {
			gO.mesh->draw();
		}
	}
}

void MainGame::DrawGame()
{
	_gameDisplay.clearDisplay(0.35f, 0.4f, 0.5f, 0.5f); //sets our background colour

	UpdateAllGameObjects();
	counter += deltaTime;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}