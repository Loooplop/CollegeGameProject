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
		DisplayManager::updateNeeded = true;
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
	static vec2f getCursorPosition()
	{
		double x, y;
		glfwGetCursorPos(DisplayManager::window, &x, &y);
		return vec2f(x, y);
	}
	static vec2f getScreenSize()
	{
		int x, y;
		glfwGetWindowSize(DisplayManager::window, &x, &y);
		return vec2f(x, y);
	}
	static void setCursorPosition(vec2f position)
	{
		glfwSetCursorPos(DisplayManager::window, position.getX(), position.getY());
	}
	static void UnInit();
	static bool getWindowCloseFlag();
	static void SwapBuffers();
	static void PollWindowEvents();
	static mat4f getPerspectiveMatrix();
private:
	DisplayManager();
	static GLFWwindow *window;
	static bool updateNeeded;
	static mat4f perspectiveMatrix;
};

