#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "defines.h"
#include "Display.h"

int main()
{
	Display display;

	glfwInit();

	display.makeWindow();

	while (!glfwWindowShouldClose(display.window) && glfwGetKey(display.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(display.window);

		glfwPollEvents();
	}

	return EXIT;
}