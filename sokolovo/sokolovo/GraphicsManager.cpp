#include "GraphicsManager.h"

#include <glad/glad.h>	// GLAD must be included before any other includes that use OpenGL
#include <GLFW/glfw3.h>

#include <iostream>
#include <cassert>

GraphicsManager::GraphicsManager()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mainWindow = nullptr;
}

int GraphicsManager::init(int width, int height, const char* title)
{
	// Create and set GLFW window
	mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(mainWindow);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set OpenGL viewport
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	return EXIT_SUCCESS;
}

int GraphicsManager::cleanup()
{
	glfwTerminate();
	return EXIT_SUCCESS;
}

void GraphicsManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//
// Direct OpenGL passthrough functions
//

/*
* Passthrough for query main window close
*/
int GraphicsManager::shouldMainWindowClose() { return glfwWindowShouldClose(mainWindow); };
/*
* Passthrough for buffer swap
*/
void GraphicsManager::swapBuffers() { glfwSwapBuffers(mainWindow); };
/*
* Passthrough for polling
*/
void GraphicsManager::pollEvents() { glfwPollEvents(); };