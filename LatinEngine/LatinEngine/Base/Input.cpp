#include "Input.h"
#include "GLFW/glfw3.h"
#include "../OpenGL/Window.h"
#include <memory.h>
#include <glm/glm.hpp>
#include "Camera.h"
namespace LATIN
{
	Key Input::m_Keys[256] = {};

	static int Keys[256];
	static int OldKeys[256];
	
	glm::dvec2 Mouse;
	glm::dvec2 MouseWorld;
	void Input::UpdateInput()
	{
		GLFWwindow* window = Window::Instance()->GetWindow();
		//Check mouse button input
		for (int i = 0; i < 8; i++)
		{
			Keys[i] = glfwGetMouseButton(window, i);

			m_Keys[i].Held = Keys[i];

			m_Keys[i].Pressed = Keys[i] && !OldKeys[i];

			m_Keys[i].Released = !Keys[i] && OldKeys[i];
		}

		//Check Keyboard input
		for (int i = 8; i < 256; i++)
		{
			
			Keys[i] = glfwGetKey(window, i);

			m_Keys[i].Held = Keys[i];

			m_Keys[i].Pressed = Keys[i] && !OldKeys[i];

			m_Keys[i].Released = !Keys[i] && OldKeys[i];
		}

		//Get mouse position on screen and world

		
		memcpy(OldKeys, Keys, 256 * sizeof(int));
		
		glfwGetCursorPos(window, &Mouse.x, &Mouse.y);

		//MouseWorld = Mouse * Camera::GetProjectionView(1.6);
	}
}