#pragma once
#include <glm/glm.hpp>

namespace LATIN
{
	class Camera
	{
	public:
		static glm::vec2 Position;
		static float Rotation;
		static glm::vec2 Size;

		static glm::mat4 GetProjectionView(float aspectRatio);
	};
}