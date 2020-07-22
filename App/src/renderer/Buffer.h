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
	void setVertex(float* vertex, unsigned int size);
	void setElement(unsigned int* elements, unsigned int size);
};

#endif