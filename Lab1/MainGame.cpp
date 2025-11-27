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

	planeMesh.loadModel("..\\res\\surface.obj");
	monkeyMesh.loadModel("..\\res\\monkey3.obj");
	ballMesh.loadModel("..\\res\\Ball.obj");
	capsuleMesh.loadModel("..\\res\\capsule.obj");
	fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag"); //new shader
	toonShader.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //new shader
	explosionShader.init("..\\res\\explosion.vert", "..\\res\\explosion.frag", "..\\res\\explosion.geom");
	rimShader.init("..\\res\\Rim.vert", "..\\res\\Rim.frag");
	waterTexture.load("..\\res\\water.jpg"); //load texture
	brickWallTexture.load("..\\res\\brickwall.jpg");
	brickGroundTexture.load("..\\res\\bricks.jpg");
	redDustTexture.load("..\\res\\redDust.jpg");
	envMapping.init("..\\res\\envMapping.vert", "..\\res\\envMapping.frag");

	player.initCamera(player.transform.GetPos(), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f, 4.0f, 1.5f, false);

	InitGameObjects();


	//counter = 1.0f;
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{

		//UpdateDeltaTime();
		gt.Update();
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
	player.Update(gt.GetDeltaTime());

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
	rimShader.setMat4("modelMatrix", gameObject.transform.GetModel());
	rimShader.setMat4("viewMatrix", player.GetViewMatrix());
	rimShader.setFloat("rimPower", 3.0f);
	rimShader.setVec3("rimColor", glm::vec3(0.8f, 0.0f, 0.0f));
	rimShader.setVec3("camPos", player.getPos());


	/*transform.SetPos(glm::vec3(1.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.5, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));*/


}

void MainGame::linkExplosionShader(GameObject& gameObject) 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	explosionShader.Bind();
	explosionShader.setMat4("transform", gameObject.transform.GetModel());
	explosionShader.setFloat("time", gt.GetDeltaTime());
}

void MainGame::linkEnvMappingShader(GameObject& gameObject)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	envMapping.Bind();
	envMapping.setMat4("transform", gameObject.transform.GetMVP(player));
	envMapping.setMat4("model", gameObject.transform.GetModel());
}

// TODO not displaying this shader
void MainGame::linkFogShader(GameObject& gameObject)
{
	fogShader.Bind();
	fogShader.setMat4("transform", gameObject.transform.GetModel());
}

void MainGame::linkToonShader(GameObject& gameObject)
{
	toonShader.setMat4("modelMatrix", gameObject.transform.GetModel());
	toonShader.setMat4("transform", gameObject.transform.GetMVP(player));
	toonShader.setVec3("lightDir", glm::normalize(glm::vec3(0.0f)));
	toonShader.setVec3("lightDir", glm::cross(-player.GetForwardVec(), player.getPos()));
}

void MainGame::InitGameObjects()
{
	monkey.init(monkeyMesh, explosionShader, waterTexture, true);
	ball.init(ballMesh, fogShader, brickWallTexture, true);
	plane.init(planeMesh, fogShader, brickGroundTexture, true);
	//fireball.init(ballMesh, fogShader, waterTexture, false);
	//fireball.transform.SetScale(glm::vec3(0.25));
	casterNPC.init(capsuleMesh, fogShader, redDustTexture, true);
	casterNPC.SetProjectile(fireball);
	casterNPC.SetPatrolPoints(glm::vec3(10, 0, 0), glm::vec3(-3, 0, 5));
}

void MainGame::UpdateAllGameObjects()
{
	// GameObject
	// positional modifiers
	// rotational modifiers
	// GameObject in_scale
	// shaders

	// casterNPC
	casterNPC.UpdateDT(gt.GetDeltaTime());
	UpdateGameObject(casterNPC,
		casterNPC.transform.GetPos(),
		casterNPC.transform.GetRot(),
		casterNPC.transform.GetScale(),
		std::bind(&MainGame::linkFogShader, this, std::placeholders::_1),
		true);


	// monkey
	UpdateGameObject(monkey,
		glm::vec3(sin(1 + gt.GetDeltaTime()), 0, 0),
		glm::vec3(0, gt.GetDeltaTime() * 0.5f, 0),
		glm::vec3(1, 1, 1),
		std::bind(&MainGame::linkExplosionShader, this, std::placeholders::_1),
		false);

	// ball
	UpdateGameObject(ball,
		glm::vec3(10, cos(1 + gt.GetDeltaTime()), -2),
		glm::vec3(0, 0, -gt.GetDeltaTime() * 0.5f),
		glm::vec3(1, 1, 1),
		std::bind(&MainGame::linkFogShader, this, std::placeholders::_1),
		false);

	// fireball
	UpdateGameObject(fireball,
		fireball.transform.GetPos(),
		fireball.transform.GetRot(),
		fireball.transform.GetScale(),
		std::bind(&MainGame::linkExplosionShader, this, std::placeholders::_1),
		true);

	// ground plane
	UpdateGameObject(plane,
		glm::vec3(0, -15.1f, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0.1f),
		std::bind(&MainGame::linkFogShader, this, std::placeholders::_1),
		false);

	
}

void MainGame::UpdateGameObject(GameObject& gO, glm::vec3 in_pos, glm::vec3 in_rot, glm::vec3 in_scale, std::function<void(GameObject&)> linkerMethod, bool altDrawingMethod)
{
	// TODO remove pos, rot and in_scale and send Transform&
	// from their built-in Update() method.

	gO.transform.SetPos(in_pos);
	gO.transform.SetRot(in_rot);
	gO.transform.SetScale(in_scale);

	if (gO.state)
	{
		gO.texture.Bind(0);
		gO.shader.Bind();
		linkerMethod(gO);
		gO.shader.Update(gO.transform, player);

		if (altDrawingMethod) {
			gO.mesh.drawVertexes();
		}
		else {
			gO.mesh.draw();
		}
	}
}



void MainGame::DrawGame()
{
	_gameDisplay.clearDisplay(0.35f, 0.4f, 0.5f, 0.5f); //sets our background colour

	UpdateAllGameObjects();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}