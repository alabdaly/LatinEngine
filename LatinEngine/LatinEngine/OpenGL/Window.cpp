#include "Window.h"
#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
namespace LATIN
{
	Window* Window::s_Instance = nullptr;

	void Window::Create(const WindowCreateInfo& info)
	{
		s_Instance = this;

		if (!glfwInit())
		{
			printf("Failed to init GLFW");
			return;
		}

		m_Window = glfwCreateWindow(info.width, info.height, info.title, info.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

		if (!m_Window)
		{
			printf("Failed to create window");
		}
		
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			printf("Failed to load glad");
			return;
		}

		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
			{
				WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
				data->Width = width;
				data->Height = height;

				glViewport(0, 0, width, height);
			});
	}
}