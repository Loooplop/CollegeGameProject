#include "DisplayManager.h"
#include "Program.h"
#include "ResourceLoader.h"
#include "EntityRenderer.h"
#include <time.h>
int main()
{
	srand(time(NULL));
	DisplayManager::Init("Test", vec2i(800, 600), vec2i(3, 3));


	Camera camera(vec3f(0, 0, -1));
	std::vector<Entity*> triangles;
	Model*model = new Model("pony.obj", Position_Texture_Normal, false);
	Texture*texture = new Texture("pony.bmp", GL_TEXTURE_2D);
	for (int y = -2; y <= 2; y++)
	{
		for (int x = -2; x <= 2; x++)
		{
			triangles.push_back(new Entity(model, texture, vec3f(15 * x, 15 * y, 0), vec3f(0, 0, 0), vec3f(1, 1, 1)));
		}
	}
	Entity light("cube.obj", "faces.bmp", vec3f(0, 0, 0), vec3f(0, 0, 0), vec3f(1, 1, 1));
	Light sun(vec3f(cos(glfwGetTime()) * 25, sin(glfwGetTime()) * 25, 0), vec3f(1, 1, 1), vec3f(1, 0.2, 0.001));
	EntityRenderer renderer;
	while (!DisplayManager::getWindowCloseFlag())
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		DisplayManager::PollWindowEvents();




		if (DisplayManager::getKeyStatus(GLFW_KEY_S))
		{
			camera.MoveBackward(2.0f);
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_W))
		{
			camera.MoveForward(2.0f);
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_A))
		{
			camera.MoveLeft(2.0f);
		}
		if (DisplayManager::getKeyStatus(GLFW_KEY_D))
		{
			camera.MoveRight(2.0f);
		}
		camera.RotateRight(DisplayManager::getCursorPosition().getX()*0.2f);
		DisplayManager::setCursorPosition(vec2f(0, 0));



		sun.setLightPosition(vec3f(cos(glfwGetTime())*25, sin(glfwGetTime()) * 25, 0));
		light.setPosition(sun.getLightPosition());

		for (int i = 0; i < triangles.size();i++)
		renderer.process(triangles[i]);


		renderer.process(&light);
		
		renderer.prepare();
		renderer.render(camera, sun);
		renderer.unprepare();




		
		if (DisplayManager::getKeyStatus(GLFW_KEY_ESCAPE))
		{
			DisplayManager::setWindowCloseFlag(true);
		}
		DisplayManager::SwapBuffers();
		DisplayManager::setCursorPosition(vec2f(0, 0));
	}
	triangles.clear();
	delete model;
	delete texture;
	DisplayManager::UnInit();
	return 0;
}