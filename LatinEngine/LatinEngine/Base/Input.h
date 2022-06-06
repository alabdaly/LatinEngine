#pragma once

namespace LATIN
{
	struct Key
	{
		bool Pressed, Held, Released;
	};

	class Input
	{
	public:
		static Key GetKey(int key) { return m_Keys[key]; };
	private:
		static void UpdateInput();
		friend class Application;
	private:
		static Key m_Keys[256];
	};
}