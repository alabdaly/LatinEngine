#include "Animation.h"
#include "../Base/TimeStep.h"
namespace LATIN
{
	void Animation::Create(const std::vector<AnimationData>& animations, uint32_t maxFramesInRow)
	{
		m_Animations = animations;
		m_MaxFramesInRow = maxFramesInRow;
	}
	void Animation::Update()
	{
		m_Time += TimeStep::GetDeltaTime();
		m_Animations[m_Column].CurrentRow = (int)(m_Time / m_Animations[m_Column].Time) % m_Animations[m_Column].MaxRows;
	}
	void Animation::Play(uint32_t column)
	{
		m_Time = 0.0f;
		m_Column = column;
	}
}