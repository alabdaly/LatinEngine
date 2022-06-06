#include "Input.h"
#include "GLFW/glfw3.h"
#include "../OpenGL/Window.h"
#include <memory.h>
namespace LATIN
{
	Key Input::m_Keys[256] = {};

	static int Keys[256];
	static int OldKeys[256];

	void Input::UpdateInput()
	{
		//Check mouse button input
		for (int i = 0; i < 8; i++)
		{
			Keys[i] = glfwGetMouseButton(Window::Instance()->GetWindow(), i);

			m_Keys[i].Held = Keys[i];

			m_Keys[i].Pressed = Keys[i] && !OldKeys[i];

			m_Keys[i].Released = !Keys[i] && OldKeys[i];
		}

		//Check Keyboard input
		for (int i = 8; i < 256; i++)
		{
			
			Keys[i] = glfwGetKey(Window::Instance()->GetWindow(), i);

			m_Keys[i].Held = Keys[i];

			m_Keys[i].Pressed = Keys[i] && !OldKeys[i];

			m_Keys[i].Released = !Keys[i] && OldKeys[i];
		}

		//Get mouse position on screen and world

		
		memcpy(OldKeys, Keys, 256 * sizeof(int));
		
	}
}