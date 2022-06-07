#include "Buffers.h"
#include <glad/glad.h>

namespace LATIN
{
	//--------Vertex Array--------
	void VertexArray::Create()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}
	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}


	//--------Vertex Buffer--------
	void VertexBuffer::Create()
	{
		glGenBuffers(1, &m_RendererID);
	}
	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::UploadData(void* data, size_t size)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}


	//--------Index Buffer--------
	void IndexBuffer::Create()
	{
		glGenBuffers(1, &m_RendererID);
	}
	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void IndexBuffer::UploadIndices(uint32_t* indices, uint32_t count)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
}