#include "Buffer.h"
#include <iostream>

Buffer::Buffer()
{
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ebID);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_vbID);
	glDeleteBuffers(1, &m_vbID);
}

void Buffer::setVertex(float *vertex, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbID);

	glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
}

void Buffer::setElement(unsigned int *elements, unsigned int size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elements, GL_STATIC_DRAW);
}
