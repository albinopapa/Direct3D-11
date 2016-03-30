#include "System.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE, LPSTR Args, INT CmdShow)
{
	System system(800, 600, Instance, CmdShow);

	return system.Run();
}

// Kind of a bad idea to do this, but I did it anyway.  D3d relies on win 
// to be initialized, and game relies on d3d and win to be initialized.
// The reason it's a bad idea, is because C++ initializes in the order they
// are declared in the header (.h) file, not the order they are here.
System::System(UINT Width, UINT Height, HINSTANCE Instance, INT CmdShow)
	:
	win( Width, Height, Instance, CmdShow, this ),
	d3d( win ),
	game( kServ, d3d, win )
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
	case WM_KEYUP:
		kServ.OnKeyRelease(static_cast<unsigned char>(wParam));
		break;
	case WM_KEYDOWN:
		kServ.OnKeyPress(static_cast<unsigned char>(wParam));
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
