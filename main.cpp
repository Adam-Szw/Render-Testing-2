#include "model.h"
#include "objReader.h"
#include "texture.h"
#include "Utilities.h"
#include "Renderer.h"
#include "Scene.h"
#include "Game.h"
#include "ShaderReader.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Maths.h"

float getRandom(float min, float max)
{
	return ((((float)rand()) / (float)RAND_MAX) * (max - min)) + min;
}

int main()
{
	Game::initializeOpenGL(800, 600, "test");

	/* Example testing setup "Monkey Dimension" */

	Scene testScene;
	Game::currentScene = &testScene;

	Camera cam;
	Game::currentCamera = &cam;

	Controls contr;
	Game::currentControls = &contr;

	Renderer::viewMatrix = Maths::mat4();
	Renderer::projectionMatrix = Maths::mat4::perspective(0.785398f, 1.25f, 0.1f, 10000.0f);

	ShaderReader::readShader(ShaderReader::shaderType::vertex, "Resources\\shaderA_vertex.shader");
	ShaderReader::readShader(ShaderReader::shaderType::fragment, "Resources\\shaderA_frag.shader");
	ShaderReader::linkShaders(ShaderReader::vertexShaders[0], ShaderReader::fragmentShaders[0]);

	/* Monkey models setup */

	Model testModel("Resources\\untitled.obj");
	Texture testTexture("Resources\\monke.png");

	Entity testEntity;
	testEntity.models.push_back(&testModel);
	testEntity.texturesMap.insert(std::make_pair(0, std::vector<Texture*>{&testTexture}));
	testEntity.modelMatrixMap.insert(std::make_pair(0, std::vector<Maths::mat4>()));

	int testMonkeyCount = 300;
	float spread = 50.0f;
	float velocity = 0.01f;
	std::vector<Maths::vec3> monkeysMovementDirection;
	std::vector<Maths::vec3> monkeysRotationAxis;

	for (int i = 0; i < testMonkeyCount; i++)
	{
		Maths::mat4 testMatrix;
		float f = getRandom(0.7f, 1.5f);
		testMatrix *= Maths::mat4::translation(Maths::vec3(getRandom(-spread, spread), getRandom(-spread, spread), getRandom(-spread, spread)));
		testMatrix *= Maths::mat4::rotation(getRandom(0.0f, 6.28f), Maths::vec3(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f)));
		testMatrix *= Maths::mat4::scale(Maths::vec3(f, f, f));
		testEntity.modelMatrixMap[0].push_back(testMatrix);
		monkeysRotationAxis.push_back(Maths::vec3(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f)));
		monkeysMovementDirection.push_back(Maths::vec3(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f)));
	}

	Game::currentScene->entities.push_back(&testEntity);
	Renderer::createRender(&testEntity, 0);

	/* Sun setup */

	Model testModel2("Resources\\sun.obj");
	Texture testTexture2("Resources\\sun_texture.png");

	Entity testEntity2;
	testEntity2.models.push_back(&testModel2);
	testEntity2.texturesMap.insert(std::make_pair(0, std::vector<Texture*>{&testTexture2}));
	testEntity2.modelMatrixMap.insert(std::make_pair(0, std::vector<Maths::mat4>({ Maths::mat4() })));

	float sunVelocity = 0.01f;
	Maths::vec3 sunMovementDirection(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f));
	Maths::vec3 sunPosition(0.0f);

	Game::currentScene->entities.push_back(&testEntity2);
	Renderer::createRender(&testEntity2, 0);

	/* Setup monkeys movement timer */
	int movementTimer = 0;
	int movementReset = 500;

	while (!glfwWindowShouldClose(Game::currentWindow))
	{
		//Reset directions
		movementTimer++;
		if (movementTimer > movementReset)
		{
			movementTimer = 0;
			sunMovementDirection = Maths::vec3(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f));
			for (int i = 0; i < testMonkeyCount; i++)
			{
				monkeysMovementDirection[i] = Maths::vec3(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f));
				monkeysRotationAxis[i] = Maths::vec3(getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f), getRandom(0.0f, 1.0f));
			}
		}

		//Move the sun
		sunPosition += sunMovementDirection * sunVelocity;
		Maths::mat4 newSunMatrix = Maths::mat4::translation(sunPosition);
		Renderer::updateEntityMatrixOrientation(Renderer::action::swap, &testEntity2, 0, std::vector<unsigned int>({ 0 }), std::vector<Maths::mat4>({ newSunMatrix }));
		Renderer::lightPositionTest = sunPosition;

		//Move the monkeys
		for (int i = 0; i < testMonkeyCount; i++)
		{
			Maths::mat4 newMonkeyMatrix = testEntity.modelMatrixMap[0][i];
			newMonkeyMatrix *= Maths::mat4::translation(monkeysMovementDirection[i] * velocity);
			newMonkeyMatrix *= Maths::mat4::rotation(0.006f, monkeysRotationAxis[i]);
			Renderer::updateEntityMatrixOrientation(Renderer::action::swap, &testEntity, 0, std::vector<unsigned int>({ (unsigned int)i }), std::vector<Maths::mat4>({ newMonkeyMatrix }));
		}
		Game::loop();
	}
	
	glfwTerminate();

	return 0;
}