#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "defines.h"
#include "Display.h"
#include "shaders.h"

int main()
{
	Display display;

	glewExperimental = GL_TRUE;
	glfwInit();

	display.makeWindow();

	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	static const GLfloat vbo[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo), vbo, GL_STATIC_DRAW);

	GLuint ProgramID = LoadShaders("Shaders/Vertex.txt", "Shaders/Fragment.txt");

	while (!glfwWindowShouldClose(display.window) && glfwGetKey(display.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ProgramID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(display.window);

		glfwPollEvents();
	}

	return EXIT;
}