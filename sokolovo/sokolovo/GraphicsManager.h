#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

struct GLFWwindow;

class GraphicsManager
{
private:
	GLFWwindow* mainWindow;
	/* Callback for resizing the window
	*/
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	GraphicsManager();

	/*
	*  Initializes the graphics manager, creating a window and checking that it
	*	worked. After this is run the window is set up and ready to render.
	*/
	int init(int width, int height, const char* title);
	/*
	* Cleanup function for normal termination
	*/
	int cleanup();

	// ====================================== //
	// Direct OpenGL passthrough functions    //
	// ====================================== //

	/*
	* Passthrough for query main window close 
	*/
	int shouldMainWindowClose();
	/*
	* Passthrough for buffer swap
	*/
	void swapBuffers();
	/*
	* Passthrough for polling
	*/
	void pollEvents();

	
};

#endif // !GRAPHICSMANAGER_H
