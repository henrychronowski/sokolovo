#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

struct GLFWwindow;

class GraphicsManager
{
private:
	GLFWwindow* mainWindow;
	int height, width;
	unsigned int shaderProgram, vertexShader, fragmentShader;
	unsigned int VBO, VAO;

	// Callback for resizing the window
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// Compile shaders from source
	void compileShaders();
	// Bind and link shader program
	// This sets the shader program
	void createShaderProgram();

public:
	GraphicsManager();

	// Get information about the monitor we're using/decide what values to use based on internal logic
	void getDisplayInformation();

	/*
	*  Initializes the graphics manager, creating a window and checking that it
	*	worked. After this is run the window is set up and ready to render.
	*/
	int init(int inWidth, int inHeight, const char* title);
	/*
	*  Initializes the graphics manager, creating a window and checking that it
	*	worked. After this is run the window is set up and ready to render.
	*/
	int init(const char* title);
	// Cleanup function for normal termination
	int cleanup();

	// Adds an object to the scene
	// Right now just takes in a triangle and manually sets it
	// Eventually this will just add to the pool I think
	// VAO and VBO for object are generated in this function
	void addStaticObjectToScene(float vertices[], int size);

	// ====================================== //
	// Graphics Pipeline Functions			  //
	// ====================================== //
	
	// Clears the buffer
	void clearBuffer();
	// Renders the singular VAO/VBO
	void renderObject();

	// ====================================== //
	// Direct OpenGL passthrough functions    //
	// ====================================== //

	// Passthrough for query main window close 
	int shouldMainWindowClose();
	// Passthrough for buffer swap
	void swapBuffers();
	// Passthrough for polling
	void pollEvents();

	
};

#endif // !GRAPHICSMANAGER_H
