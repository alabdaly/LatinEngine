#pragma once
#include <inttypes.h>
#include <vector>
namespace LATIN
{
	struct AnimationData
	{
		uint32_t CurrentRow = 0; // Current frame in a row
		uint32_t MaxRows = 1; // Total number of valid frames in a row
		float Time; // Time between each frame and the next
	};

	class Animation
	{
	public:
		void Create(const std::vector<AnimationData>& animations, uint32_t maxFramesInRow);
		void Update();
		void Play(uint32_t column);

		uint32_t GetCurrentRow() { return m_Animations[m_Column].CurrentRow; }
		uint32_t GetCurrentColumn() { return m_Column; }

		uint32_t GetMaxColumns() { return m_Animations.size(); };
		uint32_t GetMaxRows() { return m_MaxFramesInRow; }
	private:
		double m_Time = 0.0f;
		std::vector<AnimationData> m_Animations;
		uint32_t m_Column = 0; // Current column
		uint32_t m_MaxFramesInRow;
	};
}