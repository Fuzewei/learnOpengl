#pragma once
#pragma once
class IndexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int* data, unsigned int conut);
	~IndexBuffer();
	void bind()const ;
	void unBind()const;
	inline unsigned int getCount() const { return m_count; };
};