#include "DisplayManager.h"
#include <iostream>
GLFWwindow *DisplayManager::window = 0;
DisplayManager::DisplayManager()
{

}
DisplayManager::~DisplayManager()
{

}
bool DisplayManager::Init(char* windowName, vec2i windowSize, vec2i openGLVersion)
{
	bool Error = false;
	int err = glfwInit();
	window = glfwCreateWindow(windowSize.getX(), windowSize.getY(), windowName, NULL, NULL);
	glfwSetWindowSizeCallback(DisplayManager::window,DisplayManager::resize_callback);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!window)
	{
		std::cout << "Error creating window" << std::endl;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	GLenum Err = glewInit();
	Error = (err != 0) || (Err != GLEW_OK);
	glViewport(0, 0, windowSize.getX(), windowSize.getY());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


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
	return ::getPerspectiveMatrix<float>(45.0f, (float)width / (float)height, 0.1, 1000);
}