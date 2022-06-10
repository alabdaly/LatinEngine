#pragma once
#include "Window.h"
#include "Buffers.h"
#include "Texture.h"
#include "Shader.h"
#include "../Base/Camera.h"
#include <glm/glm.hpp>
#include "Animation.h"
namespace LATIN
{
	struct RenderData
	{
		glm::vec2 Position = {0, 0};
		float rotation = 0.0f;
		glm::vec2 Scale = {1, 1};
		glm::vec4 Color = { 1, 1, 1, 1 };
		Texture* texture = nullptr;
		//Animation* animation = nullptr;
		glm::vec2 TexCoordsMin = {0.0f, 0.0f};
		glm::vec2 TexCoordsMax = {1.0f, 1.0f};
	};
	class Renderer
	{
	public:
		static void Clear(const glm::vec3& color);

		static void DrawQuad(const RenderData& data);
	private:
		static void Init();

		static void StartBatch();
		static void EndBatch();

		friend class Application;
	private:
	};
}