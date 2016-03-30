#include "Game.h"
#include <time.h>


Game::Game(KeyboardServer &kServ, const Direct3D &D3D, Window &Win)
	:
	gfx( D3D, Win ),
	win( Win ),
	kbd(kServ),
	sprite_shader( D3D ),
	cam( Win ),
	player_projectile(L"Images\\ship.png", D3D)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	sprite_shader.LoadShaderFiles(L"Shaders\\Sprite_Vertex_Shader.cso",
		L"Shaders\\Sprite_Pixel_Shader.cso", D3D.GetDevice());
	ship.Init(0.0f, -1.0f, 1.0f, player_projectile, D3D);
	gfx.SetDepthState( );
}


Game::~Game()
{
}

void Game::UpdateFrame()
{
	float dt = 1.0f / 60.0f;

	cam.Update( dt );
	ship.Update( kbd, dt );

	UpdateConstantBuffers();
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateConstantBuffers()
{
	DirectX::TransformBuffer tb{};
	// View and projection stay the same for entire frame
	tb.view = DirectX::XMMatrixTranspose(cam.GetView());
	tb.projection = DirectX::XMMatrixTranspose(cam.GetProjection(win));

	// World matrix and constant buffer needs to be updated for each model
	tb.world = DirectX::XMMatrixTranspose(ship.GetWorld());
	sprite_shader.UpdateVertexConstBuffer(sizeof(tb), &tb, ship.GetConstBuffer());

}

void Game::ComposeFrame()
{
	// SetRenderTarget without parameters, renders to the backbuffer
	gfx.SetRenderTarget( );
	
	// The viewport is what defines the rendering window width and height
	// and position.  Having a multiple viewports would allow for things 
	// like a rear view mear, or split screen multiplayer.
	gfx.SetViewport( cam.GetViewport( ) );
	
	sprite_shader.Set( gfx );
	ship.Draw( gfx );
}
