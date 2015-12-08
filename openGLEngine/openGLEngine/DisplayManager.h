#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "WE_TransMatrix.h"
class DisplayManager
{
public:
	
	~DisplayManager();
	static bool Init(char* windowName, vec2i windowSize, vec2i openGLVersion);
	static void resize_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};
	static int getKeyStatus(int key)
	{
		return glfwGetKey(DisplayManager::window, key);
	}
	static void setWindowCloseFlag(bool state)
	{
		glfwSetWindowShouldClose(DisplayManager::window, state);
	}
	static void UnInit();
	static bool getWindowCloseFlag();
	static void SwapBuffers();
	static void PollWindowEvents();
	static mat4f getPerspectiveMatrix();
private:
	DisplayManager();
	static GLFWwindow *window;
};

