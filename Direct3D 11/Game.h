#pragma once
#include "Graphics.h"
#include "Window.h"
#include "KeyboardClient.h"
#include "Camera.h"
#include "Shader_Sprite.h"
#include "Ship.h"

class Game
{
public:
	Game(KeyboardServer &kServ, const Direct3D &D3D, Window &Win);
	~Game();

	void UpdateFrame();
private:
	void UpdateConstantBuffers();
	void ComposeFrame();

private:
	// Framework members
	Graphics gfx;
	Window &win;
	KeyboardClient kbd;

	// Game members
	Camera cam;
	Shader_Sprite sprite_shader;
	Ship ship;
	
	Texture player_ship, player_projectile;

};

