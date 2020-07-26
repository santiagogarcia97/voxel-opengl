#ifndef TEXTURE_H
#define TEXTURE_H

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