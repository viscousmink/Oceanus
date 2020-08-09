#ifndef SHADER
#define SHADER

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif