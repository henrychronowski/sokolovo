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

#include <glad/glad.h>	// GLAD must be included before any other includes that use OpenGL
#include <GLFW/glfw3.h>

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
	// temp shit that needs to be moved eventually
	const char* vertexSource = "#version 330 core\n""layout(location = 0) in vec3 aPos;\n""void main()\n""{\n""gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n""}\0";
	const char* fragSource = "#version 330 core\n""out vec4 FragColor;\n""void main()\n""{\n""FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n""}\0";

	// The actual main
	GraphicsManager* graphicsManager = new GraphicsManager();

	// Init managers
	//graphicsManager->init(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE); // window at specified size
	graphicsManager->init(APP_TITLE);	// window at native size

	// Manual rendering
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.0f, 0.0f
	};

	/// Make a VBO containing a triangle
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/// Compile a vertex shader from source
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	/// check for errors compiling said vertex shader
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infolog << "\n";
	}

	/// Compile a fragment shader from source
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infolog << "\n";
	}

	/// Create a shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	/// Attach shaders and link shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cerr << "ERROR::SHADER_PROGRAM::LINK FAILED\n" << infolog << "\n";
	}

	/// Set active shader program
	glUseProgram(shaderProgram);

	/// Link vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!graphicsManager->shouldMainWindowClose())
	{
		graphicsManager->clearBuffer();

		graphicsManager->swapBuffers();
		graphicsManager->pollEvents();
	}

	/// Cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Cleanup managers
	graphicsManager->cleanup();

	delete graphicsManager;

	graphicsManager = nullptr;

	return EXIT_SUCCESS;
}