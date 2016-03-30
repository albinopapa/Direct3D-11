#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Window.h"
#include <Windows.h>
#include "Game.h"
#include "KeyboardServer.h"

class System
{
public:
	System(UINT Width, UINT Height, HINSTANCE Instance, INT CmdShow);
	~System();

	LRESULT MsgHandler(UINT Message, WPARAM wParam, LPARAM lParam);
	int Run();

private:
	Window win;
	Direct3D d3d;
	KeyboardServer kServ;
	Game game;
};

