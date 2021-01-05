#include "Controls.h"
#include <iostream>

void Controls::processInputKeyboard(GLFWwindow* window)
{
    //generic part

	//this is placeholder camera controls

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        forward -= movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        forward += movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        right -= movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        right += movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        up += movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        up -= movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        roll += movementSpeed * 0.2f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        roll -= movementSpeed * 0.2f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Controls::processInputMouse(GLFWwindow* window, double x, double y)
{
	//generic part
	if (init)
	{
		lastX = x;
		lastY = y;
		init = false;
	}

	float mousexOffset = (float) ((lastX - x) * sensitivity);
    float mouseyOffset = (float) ((lastY - y) * sensitivity);
	lastX = x;
	lastY = y;

	//this is placeholder camera controls
    yaw -= mousexOffset * sensitivity;
    pitch -= mouseyOffset * sensitivity;
}
