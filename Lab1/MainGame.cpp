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
    deltaTime._deltaTimeFrameStart();
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
	sunShader.init("..\\res\\sunShader.vert", "..\\res\\sunShader.frag");
	eMapping.init("..\\res\\envMapping.vert", "..\\res\\envMapping.frag");
    adsLighting.init("..\\res\\ADS.vert", "..\\res\\ADS.frag");


	waterTexture.load("..\\res\\water.jpg"); //load texture
	brickWallTexture.load("..\\res\\brickwall.jpg");
	brickGroundTexture.load("..\\res\\bricks.jpg");
	redDustTexture.load("..\\res\\redDust.jpg");
	
    skybox.init(std::vector<std::string>{
        "..\\res\\skybox\\right.jpg",
            "..\\res\\skybox\\left.jpg",
            "..\\res\\skybox\\top.jpg",
            "..\\res\\skybox\\bottom.jpg",
            "..\\res\\skybox\\front.jpg",
            "..\\res\\skybox\\back.jpg"
    });

	player.initCamera(player.transform.GetPos(), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 2000.0f, 4.0f, 1.5f, false);

	InitGameObjects();

    counter.ResetCounter();
    deltaTime._deltaTimeFrameEnd();
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{
        counter.IncrementCounter(1);
        deltaTime._deltaTimeFrameStart();
		ProcessInput();
		UpdateAllGameObjects(deltaTime.GetDT_sec());
		DrawGame();
        deltaTime._deltaTimeFrameEnd();
        deltaTime.CapFrameRate(DESIRED_FPS);

        
        std::printf("\rDT: %.2f ms, Counter: %d\r", deltaTime.GetDT_ms(), counter.ReadCounter());
        fflush(stdout);
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;
	player.Update(deltaTime.GetDT_sec());

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
}

void MainGame::linkExplosionShader(GameObject& gameObject) 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	explosionShader.Bind();
	explosionShader.setMat4("transform", gameObject.transform.GetModel());
	explosionShader.setFloat("time", (float)counter.ReadCounter() / DESIRED_FPS * 0.5f);
}

void MainGame::linkSunShader(GameObject& gameObject)
{
	sunShader.Bind();
}

void MainGame::linkFogShader(GameObject& gameObject)
{
	fogShader.Bind();
	fogShader.setMat4("transform", gameObject.transform.GetModel());
}

void MainGame::linkToonShader(GameObject& gameObject)
{
	toonShader.Bind();
	toonShader.setMat4("modelMatrix", gameObject.transform.GetModel());
	toonShader.setMat4("transform", gameObject.transform.GetMVP(player));
	toonShader.setVec3("lightDir", glm::normalize(glm::vec3(0.0f)));
	toonShader.setVec3("lightDir", glm::cross(-player.GetForwardVec(), player.getPos()));
}

void MainGame::linkEmapping(GameObject& gameObject)
{
    eMapping.Bind();
    glBindTextureUnit(0, skybox.GetTextureID());
    glBindTextureUnit(1, brickGroundTexture.getID());
	eMapping.setMat4("model", gameObject.transform.GetModel());
    eMapping.setMat4("view", player.GetViewMatrix());
    eMapping.setMat4("projection", player.GetProjectionMatrix());
    eMapping.setVec3("cameraPos", player.getPos());
    eMapping.setInt("skybox", 0);
}

void MainGame::linkADSLighting(GameObject& gameObject)
{
    adsLighting.Bind();
    glBindTextureUnit(0, skybox.GetTextureID());    // diffuse
    glBindTextureUnit(1, redDustTexture.getID());   // specular
    adsLighting.setInt("material.diffuse", 0);
    adsLighting.setInt("material.specular", 1);
    adsLighting.setFloat("material.shininess", 32.0f);

    adsLighting.setVec3("light.position", ball.transform.GetPos());
    adsLighting.setVec3("light.ambient", glm::vec3(0.2f));
    adsLighting.setVec3("light.diffuse", glm::vec3(0.5f));
    adsLighting.setVec3("light.specular", glm::vec3(1.0f));

    adsLighting.setMat4("model", gameObject.transform.GetModel());
    adsLighting.setMat4("view", player.GetViewMatrix());
    adsLighting.setMat4("projection", player.GetProjectionMatrix());

}

void MainGame::InitGameObjects()
{
	monkey.init(monkeyMesh, explosionShader, waterTexture, true);
	ball.init(ballMesh, fogShader, brickWallTexture, true);
	plane.init(planeMesh, fogShader, brickGroundTexture, true);
	casterNPC.init(capsuleMesh, adsLighting, redDustTexture, true);
	//casterNPC.SetProjectile(fireball);
	casterNPC.SetPatrolPoints(glm::vec3(10, 0, 0), glm::vec3(-3, 0, 5));
}

void MainGame::UpdateAllGameObjects(float dt)
{
	// GameObject
	// positional modifiers
	// rotational modifiers
	// GameObject scaling
	// shaders

	// casterNPC
	casterNPC.UpdateDT(dt);
	UpdateGameObject(casterNPC,
		casterNPC.transform.GetPos(),
		casterNPC.transform.GetRot(),
		casterNPC.transform.GetScale(),
		std::bind(&MainGame::linkADSLighting, this, std::placeholders::_1),
		true);

	// monkey
	UpdateGameObject(monkey,
		glm::vec3(0, 0, 5),
        glm::vec3(0.0f, (counter.ReadCounter() / (DESIRED_FPS * 0.75f)), 0.0f),
		glm::vec3(1, 1, 1),
		std::bind(&MainGame::linkExplosionShader, this, std::placeholders::_1),
		false);

	// ball
	UpdateGameObject(ball,
        glm::vec3(cos((counter.ReadCounter() / (DESIRED_FPS * 0.75f))) * SUN_DISTANCE, sin((counter.ReadCounter() / (DESIRED_FPS * 0.75f))) * (SUN_DISTANCE * 0.25f), sin((counter.ReadCounter() / (DESIRED_FPS * 0.75f))) * SUN_DISTANCE),
		glm::vec3(0, 0, -counter.ReadCounter()/DESIRED_FPS),
		glm::vec3(3, 3, 3),
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
		glm::vec3(0, -100.0f, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(1,1,1),
		std::bind(&MainGame::linkEmapping, this, std::placeholders::_1),
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

    skybox.draw(&player);
	UpdateAllGameObjects(deltaTime.GetDT_sec());

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}