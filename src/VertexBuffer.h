#pragma once
class VertexBuffer
{
private:
	unsigned int m_RendererId;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void bind() const ;
	void unBind() const;
};