#ifndef CONTEXT_H
#define CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Context
{
public:
	Context();
	GLFWwindow* getWindow();
private:
	const GLuint WIDTH = 800, HEIGHT = 600;
	GLFWwindow* window;
};

#endif