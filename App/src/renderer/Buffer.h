#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <iostream>

class Buffer
{
private:
	unsigned int m_vbID, m_ebID;
public:
	Buffer();
	~Buffer();
	void setVertex(float* vertex, std::size_t size);
	void setElement(unsigned int* elements, std::size_t size);
};

#endif