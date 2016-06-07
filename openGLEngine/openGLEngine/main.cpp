#include "DisplayManager.h"
#include "Program.h"
#include "ResourceLoader.h"
#include "EntityRenderer.h"
#include "Terrain.h"
#include "AnimationFrame.h"
#include "FrameBuffer.h"
#include <time.h>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ImageRenderer.h"
struct GridUnit
{
	int gridX, gridY;
	Entity entity;
};
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	DisplayManager::Init("Test", vec2i(1920, 1080), vec2i(3, 3));
	ResourceLoader::InitResourceLoader();
    ResourceLoader::loadResourcesFromFile("resources.rc");
	FrameBuffer inverseColor(DisplayManager::getScreenSize().getX(), DisplayManager::getScreenSize().getY());
	ImageRenderer imgRen;
    float speed = 0.25f;
	Camera camera(vec3f(0, 1, 5));

	Light sun(vec3f(0,6,0), vec3f(1, 1, 1), vec3f(1.0f, 0.1f, 0.0f));

	EntityRenderer renderer;
	Entity *light=new Entity(ResourceLoader::getModel("field.obj"), ResourceLoader::getTexture("faces.bmp"), vec3f(-0, 0, -0), vec3f(0, 0, 0), vec3f(1, 1, 1));
	int x = (rand()%3)-3;
	while (!DisplayManager::getWindowCloseFlag())
	{
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
		
		inverseColor.bindFrameBuffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.process(light);
		renderer.prepare();
		renderer.render(camera, sun);
		renderer.unprepare();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		imgRen.render(inverseColor.getColorTexture());

		DisplayManager::SwapBuffers();
		if (DisplayManager::getKeyStatus(GLFW_KEY_ESCAPE))
		{
			DisplayManager::setWindowCloseFlag(true);
		}
	};
	delete light;
	ResourceLoader::CleanUpResourceLoader();
	DisplayManager::UnInit();
	return 0;
}