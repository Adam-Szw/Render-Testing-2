#pragma once
#include <GLFW/glfw3.h>
#include "Maths.h"

class Controls
{
public:
	double lastX = 0.0f;								//mouse movement detection
	double lastY = 0.0f;								
	bool init = true;									//used for setting first X and Y
	float sensitivity = 0.05f;
	float movementSpeed = 0.1f;

	float forward = 0.0f;
	float right = 0.0f;
	float up = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

	void processInputKeyboard(GLFWwindow* window);		//keyboard strokes
	void processInputMouse(GLFWwindow* window, double x, double y);
};


