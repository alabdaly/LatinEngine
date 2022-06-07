#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace LATIN
{
	glm::vec2 Camera::Position = {0, 0};
	float Camera::Rotation = 0.0f;
	glm::vec2 Camera::Size = { 2, 2 };

	glm::mat4 Camera::GetProjectionView(float aspectRatio)
	{
		aspectRatio *= 0.5f;
		glm::mat4 Proj = glm::ortho(-aspectRatio, aspectRatio, -0.5f, 0.5f);
		glm::mat4 View = glm::translate(glm::mat4(1.0f), { Position.x, Position.y, 0.0f }) * glm::rotate(glm::mat4(1.0f), Rotation, { 0, 0, 1 }) / glm::scale(glm::mat4(1.0f), {Size.x, Size.y, 1.0f});
		return Proj * View;
	}
}