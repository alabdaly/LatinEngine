#pragma once
#include <inttypes.h>
//Provided so we don't include glad in the header file
struct GLFWwindow;

namespace LATIN
{
	struct WindowCreateInfo
	{
		uint32_t width, height;
		const char* title;
		bool fullscreen;
	};

	class Window
	{
	public:
		void Create(const WindowCreateInfo& info);

		static Window* Instance() { return s_Instance; }

		uint32_t GetWidth() { return  m_WindowData.Width; }
		uint32_t GetHeight() { return m_WindowData.Height; }

		GLFWwindow* GetWindow() { return m_Window; }
	private:
		static Window* s_Instance;
		GLFWwindow* m_Window;

		struct WindowData
		{
			uint32_t Width = 0;
			uint32_t Height = 0;
			bool Vsync = false;
			bool Fullscreen = false;

		} m_WindowData;
	};
}