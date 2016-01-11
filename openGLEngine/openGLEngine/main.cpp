#include "DisplayManager.h"
#include "Program.h"
#include "ResourceLoader.h"
#include "EntityRenderer.h"
#include <time.h>
int main()
{
	DisplayManager::Init("Test", vec2i(800, 600), vec2i(3, 3));

	float speed = 0.5f;
	Camera camera(vec3f(0, 0, -1));

	Light sun(vec3f(0, 60, 0), vec3f(1, 1, 1), vec3f(1.0f, 0.1f, 0.0f));

	EntityRenderer renderer;
	Entity light("cube.obj", "faces.bmp", vec3f(0, 0, 0), vec3f(0, 0, 0), vec3f(1, 1, 1));
	
	while (!DisplayManager::getWindowCloseFlag())
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		DisplayManager::PollWindowEvents();
		if (DisplayManager::getKeyStatus(GLFW_KEY_S))
		{
			camera.MoveBackward(speed);
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_W))
		{
			camera.MoveForward(speed);
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_A))
		{
			camera.MoveLeft(speed*2);
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_D))
		{
			camera.MoveRight(speed*2);
		}
		camera.RotateRight(DisplayManager::getCursorPosition().getX()*0.2f);
		camera.RotateUp(DisplayManager::getCursorPosition().getY()*-0.2f);
		DisplayManager::setCursorPosition(vec2f(0, 0));

		renderer.process(&light);
		renderer.prepare();
		renderer.render(camera, sun);
		renderer.unprepare();

		DisplayManager::SwapBuffers();
		if (DisplayManager::getKeyStatus(GLFW_KEY_ESCAPE))
		{
			DisplayManager::setWindowCloseFlag(true);
		}
	};
	DisplayManager::UnInit();
	return 0;
}