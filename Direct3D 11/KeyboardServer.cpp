#include "KeyboardServer.h"



KeyboardServer::KeyboardServer()
{
	for (int i = 0; i < key_count; ++i)
	{
		key_code[i] = false;
	}
}


KeyboardServer::~KeyboardServer()
{
}

void KeyboardServer::OnKeyPress(unsigned char KeyCode)
{
	key_code[KeyCode] = true;
}

void KeyboardServer::OnKeyRelease(unsigned char KeyCode)
{
	key_code[KeyCode] = false;
}

