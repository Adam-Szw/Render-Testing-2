#include "Game.h"
#include "Renderer.h"
#include <iostream>

Scene* Game::currentScene;
GLFWwindow* Game::currentWindow;
Controls* Game::currentControls;
Camera* Game::currentCamera;

GLFWwindow* Game::initializeOpenGL(int width, int height, const char* name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetFramebufferSizeCallback(window, sizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    currentWindow = window;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    return window;
}

void Game::loop()
{
    //Update camera
    currentControls->processInputKeyboard(currentWindow);
    currentCamera->update(currentControls);
    Renderer::viewMatrix = currentCamera->viewMatrix;



    //Render contents
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Renderer::render();
    glfwSwapBuffers(currentWindow);
    glfwPollEvents();
}

void Game::sizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Game::mouseCallback(GLFWwindow* window, double x, double y)
{
    currentControls->processInputMouse(window, x, y);
}