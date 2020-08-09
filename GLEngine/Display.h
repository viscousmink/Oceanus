#ifndef DISPLAY
#define DISPLAY

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "defines.h"

class Display
{
public:
	GLFWwindow* window;
	bool makeWindow();

private:

};

#endif