#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexCode;
	std::ifstream VertexCodeStream(vertex_file_path, std::ios::in);
	if (VertexCodeStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexCodeStream.rdbuf();
		VertexCode = sstr.str();
		VertexCodeStream.close();
	}
	else 
	{
		std::cout << vertex_file_path << '\t' << "not found" << std::endl;
		getchar();
		return 0;
	}

}