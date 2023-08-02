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
	height = 0;
	width = 0;
}

int GraphicsManager::init(int inWidth, int inHeight, const char* title)
{
	// Create and set GLFW window
	mainWindow = glfwCreateWindow(inWidth, inHeight, title, NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(mainWindow);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set OpenGL viewport
	glViewport(0, 0, width, height);

	// Set GLFW callbacks
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	return EXIT_SUCCESS;
}

int GraphicsManager::init(const char* title)
{
	// Get display information
	getDisplayInformation();

	// Create and set GLFW window
	mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(mainWindow);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set OpenGL viewport
	glViewport(0, 0, width, height);

	// Set GLFW callbacks
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	return EXIT_SUCCESS;
}

int GraphicsManager::cleanup()
{
	glfwTerminate();
	return EXIT_SUCCESS;
}

void GraphicsManager::getDisplayInformation()
{
	int count;
	const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

	width = modes[count - 1].width;
	height = modes[count - 1].height;
	//delete modes;
}

void GraphicsManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
* Event/Input polling
*/
void GraphicsManager::pollEvents() 
{ 
	glfwPollEvents();
	
	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mainWindow, true);
	}
}

/*
 * Graphics Pipeline Functions
 */
void GraphicsManager::clearBuffer()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

// ====================================== //
// Direct OpenGL passthrough functions    //
// ====================================== //

/*
* Passthrough for query main window close
*/
int GraphicsManager::shouldMainWindowClose() { return glfwWindowShouldClose(mainWindow); }
/*
* Passthrough for buffer swap
*/
void GraphicsManager::swapBuffers() { glfwSwapBuffers(mainWindow); }