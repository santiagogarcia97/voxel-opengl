#ifndef CONTEXT_H
#define CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Context
{
public:
	Context();

	GLFWwindow* get_window() const;
	void set_key_callback(GLFWkeyfun callback) const;
	void set_cursor_callback(GLFWcursorposfun callback) const;
	
private:
	const GLuint m_Width = 800, m_Height = 600;
	GLFWwindow* m_Window;
};

#endif