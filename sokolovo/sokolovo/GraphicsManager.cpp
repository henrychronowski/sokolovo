#include "GraphicsManager.h"

#include <glad/glad.h>	// GLAD must be included before any other includes that use OpenGL
#include <GLFW/glfw3.h>

#include <iostream>
#include <cassert>

#define GL_LOG_SIZE 512

GraphicsManager::GraphicsManager()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mainWindow = nullptr;
	height = 0;
	width = 0;
	vertexShader = 0;	// I feel like these probably shouldn't be init to 0 but
	fragmentShader = 0;
	shaderProgram = 0;
}

void GraphicsManager::compileShaders()
{
	/// Temp hardcoded shaders
	const char* vertexSource = "#version 330 core\n""layout(location = 0) in vec3 aPos;\n""void main()\n""{\n""gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n""}\0";
	const char* fragSource = "#version 330 core\n""out vec4 FragColor;\n""void main()\n""{\n""FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n""}\0";

	// Error checking variables
	int success;
	char log[GL_LOG_SIZE];

	// Compile vertex shader from source
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Check for vertex shader compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, GL_LOG_SIZE, NULL, log);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION FAILED \n" << log << "\n";
	}

	// Compile fragment shader from source
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);

	// Check for fragment shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, GL_LOG_SIZE, NULL, log);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED \n" << log << "\n";
	}
}

void GraphicsManager::createShaderProgram()
{
	// Error checking variables
	int success;
	char log[GL_LOG_SIZE];

	// Create shader program, attach and link shaders
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// Check for link errors in shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, GL_LOG_SIZE, NULL, log);
		std::cerr << "ERROR::SHADER_PROGRAM::LINK FAILED\n" << log << "\n";
	}

	// Set shader program to active
	glUseProgram(shaderProgram);
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

	// Shader work
	compileShaders();
	createShaderProgram();

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

	// Shader work
	compileShaders();
	createShaderProgram();

	return EXIT_SUCCESS;
}

int GraphicsManager::cleanup()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();
	return EXIT_SUCCESS;
}

void GraphicsManager::getDisplayInformation()
{
	int count;
	const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

	width = modes[count - 1].width;
	height = modes[count - 1].height;
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