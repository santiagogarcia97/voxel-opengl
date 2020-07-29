#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Context.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/Buffer.h"

class Application
{
public:
	Application();
	~Application();

	int run();
private:
	const Context ctx;
	const Shader triangleShader;
	const Texture tex1;
	const VertexArray vao;
	const Buffer buff;
};