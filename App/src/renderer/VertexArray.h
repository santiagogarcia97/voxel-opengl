#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>
#include <iostream>

class VertexArray
{
private:
	unsigned int m_ID;
public:
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
};

#endif