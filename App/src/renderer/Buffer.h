#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>

class Buffer
{
public:
	Buffer();
	~Buffer();
	void set_vertex(float* vertex, std::size_t size) const;
	void set_element(unsigned int* elements, std::size_t size) const;
	
private:
	unsigned int m_VbId, m_EbId;
};

#endif