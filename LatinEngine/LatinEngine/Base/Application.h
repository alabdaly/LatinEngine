#pragma once
#include <stdint.h>

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
		bool b_Run = true;
	};
}