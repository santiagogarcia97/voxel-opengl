#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture
{
public:
	Texture(const char* text_path);
	void bind() const;
private:
	unsigned int m_Id;
	int m_Width, m_Height, m_NrChannels;
};

#endif