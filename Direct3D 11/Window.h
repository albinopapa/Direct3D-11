#pragma once
#include <Windows.h>
#include <string>

class System;
class Window
{
public:
	Window(UINT Width, UINT Height, HINSTANCE Instance, INT CmdShow, System *pSystem);
	~Window();

	void ChangeTitle(const std::wstring &NewTitle);
	HWND GetHandle()const;
	UINT GetWidth()const;
	UINT GetHeight()const;
private:
	UINT width, height;
	HWND hWnd;
	HINSTANCE hInst;

	std::wstring title, classname;
};

