#pragma once
#include "types.h"
#include <string>
#include <vector>
class Texture
{
public:
	Texture(const std::string &filePath);
	~Texture();
	void bind(unsigned int slot = 0) const;
	void unBind() const;
private:
	RenderId m_RendererID;
	std::string m_FilePath;
	int m_Width;
	int m_Height;
	int m_BPP;
	unsigned char *m_LocalBuffer;
};

