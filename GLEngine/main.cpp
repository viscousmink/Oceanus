#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include "defines.h"
#include "Display.h"
#include "shaders.h"
#include "loader.h"
#include "controls.h"
#include "Object.h"
#include "Renderer.h"

int main()
{
	Display display;
	Controls controls;
	Renderer renderer;

	glewExperimental = GL_TRUE;
	glfwInit();

	display.makeWindow();

	std::vector<Object> objects;
	Object ob;
	Object Cube;

	ob.genVao();
	ob.init("Models/suzanne.obj", "Textures/uvmap.DDS", "normal.bmp", "diffuse.DDS", "specular.DDS");

	//Cube.genVao();
	//Cube.init("Models/cube.obj", "Textures/uvmap1.DDS");

	//objects.push_back(Cube);
	objects.push_back(ob);

	while (!glfwWindowShouldClose(display.window) && glfwGetKey(display.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		controls.computeMatricesFromInputs(display.window);
		controls.move(objects[0], display.window);
		glm::mat4 View = controls.getViewMatrix();
		glm::mat4 Projection = controls.getProjectionMatrix();

		for (int i = 0; i < objects.size(); i++)
		{
			renderer.render(objects[i], Projection, View, objects[0]);
		}

		glfwSwapBuffers(display.window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT;
}