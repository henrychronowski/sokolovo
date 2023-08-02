#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

struct GLFWwindow;

class GraphicsManager
{
private:
	GLFWwindow* mainWindow;
	int height, width;
	/* Callback for resizing the window
	*/
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	GraphicsManager();

	/*
	* Get information about the monitor we're using/decide what values to use based on internal logic
	*/
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
	/*
	* Cleanup function for normal termination
	*/
	int cleanup();

	/*
	 *  Graphics Pipeline Functions
	 */
	void clearBuffer();

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
