#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "defines.h"
#include "Display.h"
#include "shaders.h"
#include "loader.h"
#include "controls.h"
#include "Object.h"

int main()
{
	Display display;
	Controls controls;

	glewExperimental = GL_TRUE;
	glfwInit();

	display.makeWindow();

	std::vector<Object> objects;

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool result = loadObj("Models/cube.obj", vertices, uvs, normals);

	if (!result)
	{
		printf("No OBJ\n");
		return EXIT_FAILURE;
	}

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

	GLuint ProgramID = LoadShaders("Shaders/Vertex.txt", "Shaders/Fragment.txt");
	GLuint MatrixID = glGetUniformLocation(ProgramID, "MVP");

	GLuint Texture = loadDDS("Textures/uvmap.DDS");
	GLuint TextureID = glGetUniformLocation(ProgramID, "myTextureSampler");

	while (!glfwWindowShouldClose(display.window) && glfwGetKey(display.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ProgramID);

		controls.computeMatricesFromInputs(display.window);
		glm::mat4 MVP = controls.getProjectionMatrix() * controls.getViewMatrix() * glm::mat4(1.0);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(display.window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(ProgramID);
	glDeleteVertexArrays(1, &vaoID);
	glfwTerminate();

	return EXIT;
}