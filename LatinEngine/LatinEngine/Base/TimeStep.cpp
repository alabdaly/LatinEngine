#include "TimeStep.h"
#include "GLFW/glfw3.h"

namespace LATIN
{
	double TimeStep::m_DeltaTime = 0.0;
	double TimeStep::m_OldTime = 0.0;

	void TimeStep::StartTime()
	{
		m_OldTime = glfwGetTime();
	}
	void TimeStep::EndTime()
	{
		m_DeltaTime = glfwGetTime() - m_OldTime;
	}
}