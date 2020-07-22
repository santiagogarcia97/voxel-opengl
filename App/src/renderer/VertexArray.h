#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>

class VertexArray
{
private:
	unsigned int m_ID;
public:
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
	void addAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
};

#endif