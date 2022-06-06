#pragma once
#include "LatinEngine/Latin.h"
#include "glad/glad.h"
class Game : public LATIN::Application
{
public:
	void Start() override
	{

	}

	void Update() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		LATIN::Input::GetKey(0).Held ? glClearColor(1, 1, 1, 1) : glClearColor(0, 0, 0, 1);
		
	}
private:

};

int main()
{
	StartLatinEngine(Game, 640, 480);
	return 0;
}