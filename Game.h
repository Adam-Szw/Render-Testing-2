#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Controls.h"
#include "Camera.h"

class Game
{
public:
	static Scene* currentScene;
	static GLFWwindow* currentWindow;
	static Controls* currentControls;
	static Camera* currentCamera;

	//also creates glfw window
	static GLFWwindow* initializeOpenGL(int width, int height, const char* name);

	static void loop();

	static void sizeCallback(GLFWwindow* window, int width, int height);

	//controls callback
	static void processInput(GLFWwindow* window);
	static void mouseCallback(GLFWwindow* window, double x, double y);

};

