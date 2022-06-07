#pragma once
#include <inttypes.h>
namespace LATIN
{
	
		enum class Filtering
		{
			Nearest = 0x2600, Linear = 0x2601
		};

	struct TextureData
	{
		const char* Path;
		Filtering MinFilter = Filtering::Nearest;
		Filtering MagFilter = Filtering::Nearest;
	};

	class Texture
	{
	public:
		void Create(const TextureData& data);

		void Bind(uint32_t slot);
		void Unbind();

		void Destroy();

		uint32_t GetRendererID() { return m_RendererID; }
	private:
		uint32_t m_RendererID;
	};
}