#include "DisplayManager.h"
#include <iostream>
GLFWwindow *DisplayManager::window = 0;
bool DisplayManager::updateNeeded = true;
mat4f DisplayManager::perspectiveMatrix = getScaleMatrix<float>(1,1,1);
DisplayManager::DisplayManager()
{

}
DisplayManager::~DisplayManager()
{

}
bool DisplayManager::Init(char* windowName, vec2i windowSize, vec2i openGLVersion, bool setVsync)
{
	bool Error = false;
	int err = glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	window = glfwCreateWindow(windowSize.getX(), windowSize.getY(), windowName, glfwGetPrimaryMonitor(), NULL);
	glfwSetInputMode(DisplayManager::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowSizeCallback(DisplayManager::window,DisplayManager::resize_callback);
	if (!window)
	{
		std::cout << "Error creating window" << std::endl;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(setVsync);
	glewExperimental = GL_TRUE;
	GLenum Err = glewInit();
	Error = (err != 0) || (Err != GLEW_OK);
	glViewport(0, 0, windowSize.getX(), windowSize.getY());
	glEnable(GL_DEPTH_TEST);
	std::cout << glfwGetWindowAttrib(DisplayManager::window, GLFW_CONTEXT_VERSION_MAJOR) << std::endl;
	std::cout << glfwGetWindowAttrib(DisplayManager::window, GLFW_CONTEXT_VERSION_MINOR) << std::endl;
	return Error;
};
void DisplayManager::PollWindowEvents()
{
	glfwPollEvents();
}
void DisplayManager::UnInit()
{
	if (DisplayManager::window != NULL)
	{
		glfwDestroyWindow(DisplayManager::window);
	}
	glfwTerminate();
};
bool DisplayManager::getWindowCloseFlag()
{
	return glfwWindowShouldClose(window);
}
void DisplayManager::SwapBuffers()
{
	glfwSwapBuffers(window);
};
mat4f DisplayManager::getPerspectiveMatrix()
{
	
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if (updateNeeded)
	{
		DisplayManager::perspectiveMatrix = ::getPerspectiveMatrix<float>(45.0f, (float)width / (float)height, 0.1, 1000);
		DisplayManager::updateNeeded = false;
	};
	return DisplayManager::perspectiveMatrix;
}