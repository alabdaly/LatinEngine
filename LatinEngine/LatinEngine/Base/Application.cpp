#include "Application.h"

namespace LATIN
{
	void Application::Run(uint32_t width, uint32_t height)
	{
		
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
		}

		//Calls OnExit function in the user class
		OnExit();
	}
}