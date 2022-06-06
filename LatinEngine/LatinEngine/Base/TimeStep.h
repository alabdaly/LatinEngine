#pragma once

namespace LATIN
{
	class TimeStep
	{
	public:
		template<typename T = double>
		static T GetDeltaTime() { return (T)m_DeltaTime; };
	private:
		static void StartTime();
		static void EndTime();

		friend class Application;
	private:
		static double m_OldTime;
		static double m_DeltaTime;
	};
}