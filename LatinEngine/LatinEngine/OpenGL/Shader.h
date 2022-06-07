#pragma once
#include <inttypes.h>
#include <glm/glm.hpp>
namespace LATIN
{
	class Shader
	{
	public:
		void Create(const char* path);
		void Create(const char* vertexSource, const char* fragmentSource);

		void Bind();
		void Unbind();

		void Destroy();

		void UploadUniformIV1(const char* name, int* values, unsigned int count);
		void UploadUniformI1(const char* name, int value);

		void UploadUniformF1(const char* name, float value);
		void UploadUniformF2(const char* name, float value1, float value2);
		void UploadUniformF3(const char* name, float value1, float value2, float value3);
		void UploadUniformMat4(const char* name, const glm::mat4& mat);
	private:
		int GetShaderLocation(const char* name);
	private:
		uint32_t m_RendererID;
	};
}