#pragma once
#include <stdint.h>
#include "../OpenGL/Window.h"
namespace LATIN
{
	class Application
	{
	public:
		void Run(uint32_t width, uint32_t height);

		virtual void Start() {}
		virtual void Update() {}
		virtual void OnExit() {}

	private:
		Window m_Window;
		bool b_Run = true;
	};
}