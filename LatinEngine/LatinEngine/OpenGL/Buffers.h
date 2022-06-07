#pragma once
#include <inttypes.h>
namespace LATIN
{
	class VertexArray
	{
	public:
		void Create();
		void Bind();
		void Unbind();

		void Destroy();
	private:
		uint32_t m_RendererID;
	};

	class VertexBuffer
	{
	public:
		void Create();
		void Bind();
		void Unbind();

		void Destroy();

		void UploadData(void* data, size_t size);
	private:
		uint32_t m_RendererID;
	};

	class IndexBuffer
	{
	public:
		void Create();
		void Bind();
		void Unbind();

		void Destroy();

		void UploadIndices(uint32_t* indices, uint32_t count);
	private:
		uint32_t m_RendererID;
	};
}