#include "Renderer.h"

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
{
	shader.bind();
	vao.bind();
	ibo.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}
