#include "System.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE, LPSTR Args, INT CmdShow)
{
	System system(800, 600, Instance, CmdShow);

	return system.Run();
}

System::System(UINT Width, UINT Height, HINSTANCE Instance, INT CmdShow)
	:
	win(Width, Height, Instance, CmdShow, this),
	game(win)
{
}

System::~System()
{
}

LRESULT System::MsgHandler(UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;

	switch (Message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		res = DefWindowProc(win.GetHandle(), Message, wParam, lParam);
	}
	return res;
}

int System::Run()
{
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		game.UpdateFrame();
	}
	return 0;
}
