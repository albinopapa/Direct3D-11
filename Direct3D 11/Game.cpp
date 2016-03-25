#include "Game.h"



Game::Game( const Direct3D &D3D, Window &Win)
	:
	gfx( D3D, Win ),
	win( Win ),
	sprite_shader( D3D ),
	ship( D3D ),
	cam( Win )
{
	sprite_shader.LoadShaderFiles( "Shaders\\Sprite_Vertex_Shader.cso",
								   "Shaders\\Sprite_Pixel_Shader.cso",
								   D3D.GetDevice( ) );
	
}


Game::~Game()
{
}

void Game::UpdateFrame()
{
	DirectX::TransformBuffer tb{};
	float dt = 1.0f / 60.0f;
	cam.Update( dt );
	ship.Update( dt );

	// View and projection stay the same for entire frame
	tb.view = DirectX::XMMatrixTranspose(cam.GetView( ));
	tb.projection = DirectX::XMMatrixTranspose( cam.GetProjection( win ));

	// World matrix and constant buffer needs to be updated for each model
	tb.world = DirectX::XMMatrixTranspose( ship.GetWorld());
	sprite_shader.UpdateVertexConstBuffer( sizeof( tb ), &tb, ship.GetConstBuffer( ) );


	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	gfx.SetRenderTarget( );
	gfx.SetViewport( cam.GetViewport( ) );
	
	sprite_shader.Set( gfx );

	ship.Draw( gfx );
}
