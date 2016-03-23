#pragma once
#include "Graphics.h"
#include "Window.h"

class Game
{
public:
	Game(Window &Win);
	~Game();

	void UpdateFrame();
private:
	void ComposeFrame();

private:
	Graphics gfx;
	Window &win;
};

