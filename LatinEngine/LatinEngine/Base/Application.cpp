#include "Application.h"
#include <GLFW/glfw3.h>
#include "TimeStep.h"
#include "Input.h"

#include "../OpenGL/Renderer.h"

namespace LATIN
{
	void Application::Run(uint32_t width, uint32_t height)
	{
		//Create Window
		m_Window.Create({ width, height, "Latin Engine", false });

		//Init renderer (Yeah obvious)
		Renderer::Init();

		// Calls the Start function in the user class
		Start();

		while (b_Run)
		{ 
			
			//Start Timer
			TimeStep::StartTime();

			//Check if the close button had been clicked
			b_Run = !glfwWindowShouldClose(m_Window.GetWindow());

			//Update Input
			Input::UpdateInput();
			//Start Rendering Batch
			Renderer::StartBatch();
			//Calls the Update function in the user class
			Update();

			//End Render Batch
			Renderer::EndBatch();
			//Get Input and Update Screen
			glfwPollEvents();
			glfwSwapBuffers(m_Window.GetWindow());
			
			//End Timer
			TimeStep::EndTime();
		}

		//Calls OnExit function in the user class
		OnExit();
	}
}