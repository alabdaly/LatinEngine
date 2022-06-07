#pragma once
#include "LatinEngine/Latin.h"

class Game : public LATIN::Application
{
public:
	void Start() override
	{
		texture.Create({ "Assets/Textures/UwU.png" });
		animation.Create({ {0, 7, 0.016f} }, 7);
	}

	void Update() override
	{
		animation.Update();
		LATIN::Input::GetKey(0).Held ? LATIN::Renderer::Clear({ 1, 1, 1 }) : LATIN::Renderer::Clear({ 0, 0, 0 });
		LATIN::RenderData data;
		data.texture = &texture;
		data.animation = &animation;
		LATIN::Renderer::DrawQuad(data);
	}
private:
	LATIN::Texture texture;
	LATIN::Animation animation;
};

int main()
{
	StartLatinEngine(Game, 640, 480);
	return 0;
}