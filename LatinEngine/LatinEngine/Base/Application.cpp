#include "Application.h"
#include <GLFW/glfw3.h>

namespace LATIN
{
	void Application::Run(uint32_t width, uint32_t height)
	{
		m_Window.Create({ width, height, "Latin Engine", false });
		// Calls the Start function in the user class
		Start();

		while (b_Run)
		{
			//Update Input

			//Start Rendering Batch

			//Calls the Update function in the user class
			Update();

			//End Render Batch

			//Get Input and Update Screen
			glfwPollEvents();
			glfwSwapBuffers(m_Window.GetWindow());
		}

		//Calls OnExit function in the user class
		OnExit();
	}
}