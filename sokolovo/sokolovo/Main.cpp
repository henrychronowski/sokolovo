/*
* Asteroids clone project
* Henry Chronowski
* 
* This projecct is built with the goal of creating a clone of the asteroids game from scratch 
*	using OpenGL. The hopeful extension of this is to in the process build a usable personal
*	OpenGL library for the purpose of easily creating 2D games like this in the future.
* 
* References:
* https://learnopengl.com/In-Practice/2D-Game/Setting-up
*	Used as the basis for the OpenGL framework although my approach differs in many ways
* 
*/

#include <iostream>
#include <cassert>

#include "GraphicsManager.h"

//#include <glad/glad.h>	// GLAD must be included before any other includes that use OpenGL
//#include <GLFW/glfw3.h>

// Base params, should be read from file at some point probably
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define APP_TITLE "I may or may not be incompetent"

/*
* General Path:
*	- Init
*	- Run Render/Game loop
*	- Cleanup
*/
int main()
{
	/// temp shit that needs to be moved eventually

	// The actual main
	GraphicsManager* graphicsManager = new GraphicsManager();

	// Init managers
	graphicsManager->init(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE); // window at specified size
	//graphicsManager->init(APP_TITLE);	// window at native size

	// Manual rendering
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

		graphicsManager->addStaticObjectToScene(vertices, 9);

	while (!graphicsManager->shouldMainWindowClose())
	{
		graphicsManager->clearBuffer();

		// Render
		graphicsManager->renderObject();
		graphicsManager->swapBuffers();

		// Poll events/input
		graphicsManager->pollEvents();	// currently processes input
	}

	// Cleanup managers
	graphicsManager->cleanup();

	delete graphicsManager;

	graphicsManager = nullptr;

	return EXIT_SUCCESS;
}