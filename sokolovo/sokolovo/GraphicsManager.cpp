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
	VBO = 0;
	VAO = 0;
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
	if (vertexShader == 0 || fragmentShader == 0)
	{
		std::cerr << "WARNING::SHADER_PROGRAM::SHADERS_NOT_COMPILED\n" << "Attempting to compile shaders...\n";
		compileShaders();
	}

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

	// Cleanup shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
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
	glDeleteProgram(shaderProgram);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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

void GraphicsManager::pollEvents() 
{ 
	glfwPollEvents();
	
	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mainWindow, true);
	}
}

void GraphicsManager::addStaticObjectToScene(float vertices[], int size)
{

	// Generate buffers and arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);	//binding the VAO first makes the VBO following bound on the call to glVertexAttribPointer

	// Bind & set VBO(s)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

	// Configure vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

// ====================================== //
// Graphics Pipeline Functions			  //
// ====================================== //

void GraphicsManager::clearBuffer()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsManager::renderObject()
{
	glBindVertexArray(VAO);	// Not technically necessary given there is only one but will be eventually necessary
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

// ====================================== //
// Direct OpenGL passthrough functions    //
// ====================================== //

int GraphicsManager::shouldMainWindowClose() { return glfwWindowShouldClose(mainWindow); }
void GraphicsManager::swapBuffers() { glfwSwapBuffers(mainWindow); }