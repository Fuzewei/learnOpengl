#pragma once
#include<vector>
#include <src/utils/utils.h>
struct  VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;
	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
	}
};

class VertexBufferLayout 
{
public:
	template<typename T>
	void push(unsigned int count)
	{
		ASSERT(false);
	}
	template<>
	void push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count , GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}
	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count , GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count , GL_TRUE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}
	inline std::vector<VertexBufferElement> getElements() const { return m_Elements; }
	inline unsigned int  getStride() const { return m_Stride; }
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
 };
