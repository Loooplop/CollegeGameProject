#include "DisplayManager.h"
#include "Program.h"
#include "ResourceLoader.h"
#include "EntityRenderer.h"
#include "Terrain.h"
#include <time.h>
#include <stdlib.h> 
struct GridUnit
{
	int gridX, gridY;
	Entity entity;
};
int main()
{
	DisplayManager::Init("Test", vec2i(800, 600), vec2i(3, 3));
	ResourceLoader::InitResourceLoader();

	ResourceLoader::loadModel("floor", false);
	ResourceLoader::loadModel("unit2", false);
	ResourceLoader::loadTexture("floortex", GL_TEXTURE_2D);
	float speed = 0.5f;
	Camera camera(vec3f(0, 1, 5));

	Light sun(vec3f(6, 6, -6), vec3f(1, 1, 1), vec3f(1.0f, 0.1f, 0.0f));

	EntityRenderer renderer;
	Entity light(ResourceLoader::getModel("floor"), ResourceLoader::getTexture("floortex"), vec3f(-8, 0, -8), vec3f(0, 0, 0), vec3f(1, 1, 1));
	Entity Unit(ResourceLoader::getModel("unit2"), ResourceLoader::getTexture("unit001tex"), vec3f(2, 0, 0), vec3f(0, 0, 0), vec3f(1, 1, 1));

	int x = (rand()%3)-3;
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
		if (DisplayManager::getKeyStatus(GLFW_KEY_UP))
		{
			Unit.move(vec3f(0, 0, -2));
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_DOWN))
		{
			Unit.move(vec3f(0, 0, 2));
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_LEFT))
		{
			Unit.move(vec3f(-2, 0, 0));
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_RIGHT))
		{
			Unit.move(vec3f(2, 0, 0));
		}
		camera.RotateRight(DisplayManager::getCursorPosition().getX()*0.2f);
		camera.RotateUp(DisplayManager::getCursorPosition().getY()*-0.2f);
		DisplayManager::setCursorPosition(vec2f(0, 0));


		renderer.process(&light);
		renderer.process(&Unit);
		renderer.prepare();
		renderer.render(camera, sun);
		renderer.unprepare();

		DisplayManager::SwapBuffers();
		if (DisplayManager::getKeyStatus(GLFW_KEY_ESCAPE))
		{
			DisplayManager::setWindowCloseFlag(true);
		}
	};
	ResourceLoader::CleanUpResourceLoader();
	DisplayManager::UnInit();
	return 0;
}