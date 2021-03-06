#pragma once
#include "Graphics.h"
#include "Window.h"
#include "Camera.h"
#include "Shader_Sprite.h"
#include "Ship.h"

class Game
{
public:
	Game(const Direct3D &D3D, Window &Win);
	~Game();

	void UpdateFrame();
private:
	void ComposeFrame();

private:
	Graphics gfx;
	Window &win;
	Camera cam;
	Shader_Sprite sprite_shader;
	//Ship ship;
	Ship model_test[100];
	Texture tex_test;
};

