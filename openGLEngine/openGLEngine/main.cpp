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


	std::vector<Entity*> triangles;
	Model*model = new Model("cube.obj", Position_Texture_Normal, false);
	Texture*texture = new Texture("faces.bmp", GL_TEXTURE_2D);
	for (int z = 0; z < 20; z++)
	{
		for (int y = 0; y <20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				triangles.push_back(new Entity(model, texture, vec3f(20 * x, 20 * y, 20 * z), vec3f(0, 0, 0), vec3f(1, 1, 1)));
			}
		}
	}
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




		light.setPosition(sun.getLightPosition());


		for (int i = 0; i < triangles.size(); i++)
		{
			renderer.process(triangles[i]);
		};
		renderer.process(&light);
		renderer.prepare();
		renderer.render(camera, sun);
		renderer.unprepare();




		
		DisplayManager::SwapBuffers();
		DisplayManager::setCursorPosition(vec2f(0, 0));

		if (DisplayManager::getKeyStatus(GLFW_KEY_ESCAPE))
		{
			DisplayManager::setWindowCloseFlag(true);
		}
	}
	for (int i = 0; i < triangles.size(); i++)
		delete triangles[i];

	triangles.clear();
	delete model;
	delete texture;
	DisplayManager::UnInit();
	return 0;
}