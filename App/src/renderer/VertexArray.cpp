#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Id);
	bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_Id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::add_attrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const
{
	bind();
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}
