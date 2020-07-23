#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void bind() const;
	static void unbind();
	void add_attrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;
private:
	unsigned int m_Id;
};

#endif