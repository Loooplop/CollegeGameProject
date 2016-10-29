#include "DisplayManager.h"
#include "Program.h"
#include "ResourceLoader.h"
#include "Terrain.h"
#include "AnimationFrame.h"
#include "FrameBuffer.h"
#include <time.h>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
#include "MasterRenderer.h"
int main()
{
	//Debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Constants
	const float speed = 0.25f;

	//Engine Inits
	DisplayManager::Init("Test", vec2i(1920, 1080), vec2i(3, 3), false);
	ResourceLoader::InitResourceLoader();
    ResourceLoader::loadResourcesFromFile("resources.rc");

	//Renderers
	MasterRenderer masRen;

	//Scene Components
	Camera camera(vec3f(0, 1, 0));
	Light sun(vec3f(0, 6, 0), vec3f(1, 1, 1), vec3f(1.0f, 0.1f, 0.0f));

	//Scene Resources
	FrameBuffer *inverseColor=new FrameBuffer(DisplayManager::getScreenSize().getX(), DisplayManager::getScreenSize().getY());
	Entity lightPosition(ResourceLoader::getModel("sphere.obj"), ResourceLoader::getTexture("faces.bmp"), vec3f(0, 0, 0), vec3f(0, 0, 0), vec3f(0.2, 0.2, 0.2));
	Text *depthName = new Text("Depth Texture",ResourceLoader::getFont("default"),vec2f(0,1080-64),vec3f(1,0,1));
	Text *numOfObjects = new Text(" ", ResourceLoader::getFont("default"), vec2f(0, 1080 - 128), vec3f(1, 0, 0));
	Text *FPS = new Text(" ", ResourceLoader::getFont("default"), vec2f(0, 1080 - 128 - 64), vec3f(1, 1, 0));
	//Main Loop
	float time = 1;
	float delta = 1;
	while (!DisplayManager::getWindowCloseFlag())
	{
		time = glfwGetTime();
		DisplayManager::PollWindowEvents();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//Input
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
		camera.RotateUp(DisplayManager::getCursorPosition().getY()*0.2f);
		DisplayManager::setCursorPosition(vec2f(0, 0));
		//Update
		












		//Rendering
		depthName->clear();
		depthName->add("Time Between Frame: ");
		depthName->add(1/delta);

		FPS->clear();
		FPS->add("Light Position");
		FPS->add(lightPosition.getPosition());

		masRen.process(&lightPosition);

		masRen.process(depthName);
		masRen.process(FPS);
		
		masRen.prepare();
		masRen.render(camera, sun);
		masRen.unprepare();

		DisplayManager::SwapBuffers();

		//Frames per second
		delta = (glfwGetTime() - time);

		//Final Checks and System Input
		if (DisplayManager::getKeyStatus(GLFW_KEY_ESCAPE))
		{
			DisplayManager::setWindowCloseFlag(true);
		}
	};

	//Cleaning up and Releasing Allocated Memory
	masRen.cleanUp();
	delete depthName;
	delete FPS;
	delete numOfObjects;
	delete inverseColor;
	ResourceLoader::CleanUpResourceLoader();
	DisplayManager::UnInit();

	//Debug
	_CrtDumpMemoryLeaks();
	return 0;
}