#include "Game.h"
#include <time.h>


Game::Game( const Direct3D &D3D, Window &Win)
	:
	gfx( D3D, Win ),
	win( Win ),
	sprite_shader( D3D ),
	cam( Win ),
	tex_test(L"Images\\LightingTricks.png", D3D)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	sprite_shader.LoadShaderFiles( L"Shaders\\Sprite_Vertex_Shader.cso",
								   L"Shaders\\Sprite_Pixel_Shader.cso",
								   D3D.GetDevice( ) );
	for (int i = 0; i < 100; ++i)
	{
		float x = static_cast<float>(rand() % 100 - 50);
		float y = static_cast<float>(rand() % 100 - 50);
		float z = static_cast<float>(rand() % 100 - 50);

		model_test[i].Init(x, y, z, tex_test, D3D);
	}
	gfx.SetDepthState( );
}


Game::~Game()
{
}

void Game::UpdateFrame()
{
	DirectX::TransformBuffer tb{};
	float dt = 1.0f / 60.0f;

	cam.Update( dt );
	for (int i = 0; i < 100; ++i)
	{
		model_test[i].Update(0.0f);
	}
	//ship.Update( dt );

	// View and projection stay the same for entire frame
	tb.view = DirectX::XMMatrixTranspose(cam.GetView( ));
	tb.projection = DirectX::XMMatrixTranspose( cam.GetProjection( win ));

	// World matrix and constant buffer needs to be updated for each model
	for (int i = 0; i < 100; ++i)
	{
		tb.world = DirectX::XMMatrixTranspose(model_test[i].GetWorld());
		sprite_shader.UpdateVertexConstBuffer(sizeof(tb), &tb, model_test[i].GetConstBuffer());
	}
	/*tb.world = DirectX::XMMatrixTranspose( ship.GetWorld());
	sprite_shader.UpdateVertexConstBuffer( sizeof( tb ), &tb, ship.GetConstBuffer( ) );*/


	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	gfx.SetRenderTarget( );
	gfx.SetViewport( cam.GetViewport( ) );
	
	sprite_shader.Set( gfx );

	for (int i = 0; i < 100; ++i)
	{
		model_test[i].Draw(gfx);
	}
	//ship.Draw( gfx );
}
