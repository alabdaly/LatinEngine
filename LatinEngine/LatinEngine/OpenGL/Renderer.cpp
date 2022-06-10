#include "Renderer.h"
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"

namespace LATIN
{
	struct Vertex
	{
		glm::vec2 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexID;
	};

	struct RendererData
	{
		Vertex* VertexBase = nullptr;
		Vertex* VertexPointer = nullptr;

		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertecies = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		uint32_t IndexCount = 0;

		VertexArray vertexArray;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		glm::vec4 Transforms[4];

		Shader shader;

		static const uint32_t MaxTextureSlots = 32;
		Texture *Textures[MaxTextureSlots];

		uint32_t TextureSlotIndex = 1; // 0 is pure white
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		s_Data.VertexBase = new Vertex[s_Data.MaxVertecies];

		s_Data.vertexArray.Create();
		s_Data.vertexArray.Bind();

		s_Data.vertexBuffer.Create();
		s_Data.vertexBuffer.Bind();

		s_Data.indexBuffer.Create();
		s_Data.indexBuffer.Bind();

		uint32_t *Indices = new uint32_t [s_Data.MaxIndices];

		uint32_t offset = 0;
		for (int i = 0; i < s_Data.MaxIndices; i+=6)
		{
			Indices[i + 0] = offset;
			Indices[i + 1] = offset+1;
			Indices[i + 2] = offset+2;

			Indices[i + 3] = offset+2;
			Indices[i + 4] = offset+3;
			Indices[i + 5] = offset;

			offset += 4;
		}

		s_Data.indexBuffer.UploadIndices(Indices, s_Data.MaxIndices);

		delete[] Indices;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));

		s_Data.Transforms[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.Transforms[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.Transforms[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.Transforms[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_Data.shader.Create("Assets/Shaders/shader.shader");
		s_Data.shader.Bind();

		int32_t samplers[s_Data.MaxTextureSlots];
		for (int32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		s_Data.shader.UploadUniformIV1("u_Textures", samplers, s_Data.MaxTextureSlots);
	}

	void Renderer::StartBatch()
	{
		s_Data.IndexCount = 0;
		s_Data.TextureSlotIndex = 1;
		s_Data.VertexPointer = s_Data.VertexBase;

		float aspectRatio = (float)Window::Instance()->GetWidth() / (float)Window::Instance()->GetHeight();
		s_Data.shader.UploadUniformMat4("ProjView", Camera::GetProjectionView(aspectRatio));
		
	}

	void Renderer::EndBatch()
	{
		if (!s_Data.IndexCount)
			return;

		s_Data.vertexArray.Bind();

		size_t dataSize = (uint8_t*)s_Data.VertexPointer - (uint8_t*)s_Data.VertexBase;
		s_Data.vertexBuffer.UploadData(s_Data.VertexBase, dataSize);

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if(s_Data.Textures[i])
				s_Data.Textures[i]->Bind(i);
		}

		glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawQuad(const RenderData& data)
	{
		if (s_Data.IndexCount >= s_Data.MaxIndices)
		{
			EndBatch();
			StartBatch();
		}
		
		float texID = 0.0f;
		glm::vec2 TexCoordMin = data.TexCoordsMin;
		glm::vec2 TexCoordMax = data.TexCoordsMax;
		
		if (data.texture)
		{
			for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
			{
				if (s_Data.Textures[i]->GetRendererID() == data.texture->GetRendererID())
				{
					texID = (float)i;
					break;
				}
			}

			if (texID == 0.0f)
			{
				texID = (float)s_Data.TextureSlotIndex;
				s_Data.Textures[s_Data.TextureSlotIndex] = data.texture;
				s_Data.TextureSlotIndex++;
			}
		}

		

		

		glm::vec2 TexCoords[4]
		{
			{TexCoordMin.x, TexCoordMax.y},
			{TexCoordMax.x, TexCoordMax.y},
			{TexCoordMax.x, TexCoordMin.y},
			{TexCoordMin.x, TexCoordMin.y}
		};

		

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { data.Position.x, data.Position.y, 0.0f }) * glm::rotate(glm::mat4(1.0f), data.rotation, { 0, 0, 1 }) * glm::scale(glm::mat4(1.0f), {data.Scale.x, data.Scale.y, 1.0f});

		for (int i = 0; i < 4; i++)
		{
			s_Data.VertexPointer->Position = transform * s_Data.Transforms[i];
			s_Data.VertexPointer->Color = data.Color;
			s_Data.VertexPointer->TexCoord = TexCoords[i];
			s_Data.VertexPointer->TexID = texID;
			s_Data.VertexPointer++;
		}
		s_Data.IndexCount += 6;
	}

	void Renderer::Clear(const glm::vec3& color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, 1.0f);
	}
	
}