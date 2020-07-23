#include "Buffer.h"

Buffer::Buffer()
{
	glGenBuffers(1, &m_VbId);
	glGenBuffers(1, &m_EbId);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_VbId);
	glDeleteBuffers(1, &m_EbId);
}

void Buffer::set_vertex(float *vertex, std::size_t size) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VbId);

	glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
}

void Buffer::set_element(unsigned int *elements, std::size_t size) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EbId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elements, GL_STATIC_DRAW);
}
