#include "Context.h"
#include <iostream>

Context::Context()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_Window = glfwCreateWindow(m_Width, m_Height, "OpenGL", nullptr, nullptr);
    if (m_Window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
    }

    glViewport(0, 0, m_Width, m_Height);
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// OpenGL Settings
    glEnable(GL_DEPTH_TEST);
}

GLFWwindow* Context::get_window() const
{
    return m_Window;
}

void Context::set_key_callback(GLFWkeyfun callback) const
{
    glfwSetKeyCallback(m_Window, callback);
}

void Context::set_cursor_callback(GLFWcursorposfun callback) const
{
    glfwSetCursorPosCallback(m_Window, callback);
}
