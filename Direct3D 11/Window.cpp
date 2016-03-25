#include "Window.h"
#include "System.h"

LRESULT CALLBACK WndProc(HWND WinHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;
	System *system = (System *)GetWindowLongPtr(WinHandle, GWLP_USERDATA);

	if (system)
	{
		res = system->MsgHandler(Message, wParam, lParam);
	}
	else
	{
		res = DefWindowProc(WinHandle, Message, wParam, lParam);
	}

	return res;
}
Window::Window(UINT Width, UINT Height, HINSTANCE Instance, INT CmdShow, System *pSystem)
	:
	width(Width),
	height(Height),
	hInst(Instance)
{
	// Initialize, register, adjust size, create, update user
	// data and show window
	classname = L"MyClass";
	title = L"Direct3D Framework";
	int ex_style = WS_EX_OVERLAPPEDWINDOW;
	int style = WS_OVERLAPPEDWINDOW;

	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = Instance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = classname.data();
	
	RegisterClassEx(&wc);

	INT x = 100, y = 100;
	RECT r{ x, y, x + static_cast<INT>(width), y + static_cast<INT>(height) };
	AdjustWindowRectEx(&r, style, FALSE, ex_style );

	hWnd = CreateWindowEx(
		ex_style, classname.data(), title.data(), style, r.left, r.top, r.right - r.left,
		r.bottom - r.top, nullptr, nullptr, Instance, pSystem);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pSystem));

	ShowWindow(hWnd, CmdShow);
}

Window::~Window()
{
	UnregisterClass(classname.data(), hInst);
}

void Window::ChangeTitle(const std::wstring & NewTitle)
{
	title = NewTitle;
}

HWND Window::GetHandle() const
{
	return hWnd;
}

UINT Window::GetWidth() const
{
	return width;
}

UINT Window::GetHeight() const
{
	return height;
}
