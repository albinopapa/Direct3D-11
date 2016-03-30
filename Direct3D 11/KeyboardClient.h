#pragma once

class KeyboardServer;
class KeyboardClient
{
public:
	KeyboardClient(KeyboardServer &kServ);
	~KeyboardClient();

	bool KeyPressed(unsigned char KeyCode)const;
	bool KeyReleased(unsigned char KeyCode)const;
private:
	KeyboardServer& server;
};

