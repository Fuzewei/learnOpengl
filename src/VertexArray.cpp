#include "VertexArray.h"
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	bind();
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unBind()const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::addVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, 
			element.normalized, layout.getStride(),(const void *)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}
