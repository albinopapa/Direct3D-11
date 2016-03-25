#pragma once
#include "Model.h"
#include "Texture.h"
#include "Graphics.h"
#include <vector>

class Ship
{
public:
	Ship( );
	Ship( const Direct3D &D3D );
	~Ship();
	
	void Update(float DeltaTime);

	DirectX::XMMATRIX GetWorld()const;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> &GetConstBuffer()const;
	void Draw( Graphics &Gfx );

private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 orientation;

	Model_Position_Texcoord mesh;
	// Constant buffer 
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer;
	// Texture
	Texture texture;
};

