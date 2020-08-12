#ifndef CONTROL
#define CONTROL

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"

class Controls
{
public:
	
	Controls()
	{
		position = glm::vec3(0, 0, 5);
	}

	glm::mat4 getViewMatrix() { return ViewMatrix; }
	glm::mat4 getProjectionMatrix() { return ProjectionMatrix; }

	void move(Object & obj, GLFWwindow* window)
	{
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			obj.translateModelMatrix(0.0, 0.01, 0.0);
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			obj.translateModelMatrix(0.0, -0.01, 0.0);
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			obj.translateModelMatrix(0.01, 0.0, 0.0);
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			obj.translateModelMatrix(-0.01, 0.0, 0.0);
		}
	}

	void computeMatricesFromInputs(GLFWwindow* window)
	{
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		double xpos, ypos;
		int width, height;
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width / 2, height / 2);

		horizontalAngle += mouseSpeed * float(width / 2 - xpos);
		verticalAngle += mouseSpeed * float(height / 2 - ypos);

		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 right(
			sin(horizontalAngle - (3.14f / 2.0f)),
			0,
			cos(horizontalAngle - (3.14f / 2.0f))
		);

		glm::vec3 up = glm::cross(right, direction);

		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}

		float FoV = initialFOV;

		ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
		ViewMatrix = glm::lookAt(
			position,
			position + direction,
			up
		);

		lastTime = currentTime;
	}

private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 position;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFOV = 45.0f;
	float speed = 3.0f;
	float mouseSpeed = 0.005f;
};

#endif