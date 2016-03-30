#include "KeyboardClient.h"
#include "KeyboardServer.h"


KeyboardClient::KeyboardClient(KeyboardServer &kServ)
	:
	server(kServ)
{
}


KeyboardClient::~KeyboardClient()
{
}

bool KeyboardClient::KeyPressed(unsigned char KeyCode)const
{
	return server.key_code[KeyCode];
}

bool KeyboardClient::KeyReleased(unsigned char KeyCode)const
{
	return !server.key_code[KeyCode];
}
