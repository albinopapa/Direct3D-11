#pragma once

class KeyboardServer
{
public:
	friend class KeyboardClient;

	KeyboardServer();
	~KeyboardServer();

	void OnKeyPress(unsigned char KeyCode);
	void OnKeyRelease(unsigned char KeyCode);

private:
	static const unsigned int key_count = 256;
	bool key_code[key_count];
};

