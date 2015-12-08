#include "DisplayManager.h"
#include "Program.h"
#include "ResourceLoader.h"
int main()
{
	DisplayManager::Init("Test", vec2i(800, 600), vec2i(3, 3));

	Program basic("vertex.vs", "fragment.fs");

	Model triangle("triangle.obj", Position_Texture_Normal, false);

	while (!DisplayManager::getWindowCloseFlag())
	{

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		basic.start();
		triangle.Render();
		basic.stop();
		
		DisplayManager::SwapBuffers();
		DisplayManager::PollWindowEvents();
	}
	DisplayManager::UnInit();
	return 0;
}