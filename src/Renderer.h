#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
class Renderer
{
public :
	void draw(const VertexArray & vao, const IndexBuffer &ibo, const Shader &shader);
private:

};

