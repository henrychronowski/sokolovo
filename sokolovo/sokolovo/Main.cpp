#include <iostream>
#include <cassert>

#include "GraphicsManager.h"

#include <glad/glad.h>	// GLAD must be included before any other includes that use OpenGL
#include <GLFW/glfw3.h>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define APP_TITLE "I may or may not be incompetent"

int main()
{
	GraphicsManager* graphicsManager = new GraphicsManager();

	// Init managers
	graphicsManager->init(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE);

	//glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	//if (window == NULL)
	//{
	//	std::cout << "Failed to create GLFW window\n";
	//	glfwTerminate();
	//	return EXIT_FAILURE;
	//}
	//glfwMakeContextCurrent(window);

	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//{
	//	std::cout << "Failed to initialize GLAD\n";
	//	glfwTerminate();
	//	return EXIT_FAILURE;
	//}

	//glViewport(0, 0, 800, 600);

	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!graphicsManager->shouldMainWindowClose())
	{
		graphicsManager->swapBuffers();
		graphicsManager->pollEvents();
	}

	// Cleanup managers
	graphicsManager->cleanup();

	delete graphicsManager;

	graphicsManager = nullptr;

	return EXIT_SUCCESS;
}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}