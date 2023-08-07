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
	graphicsManager->init(APP_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT); // window at specified size
	//graphicsManager->init(APP_TITLE);	// window at native size

	// Manual rendering
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,		// Top right
		 0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		// bottom left
		-0.5f,  0.5f, 0.0f		// top left
	};

		graphicsManager->addStaticObjectToScene(vertices, 12);

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