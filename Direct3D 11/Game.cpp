#include "Game.h"



Game::Game(Window &Win)
	:
	gfx(Win),
	win(Win)
{
}


Game::~Game()
{
}

void Game::UpdateFrame()
{
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{

	gfx.Render();
}
