#pragma once
#include "KeyboardClient.h"
#include "Model_Position_Texcoord.h"
#include "Texture.h"
#include "Graphics.h"
#include <vector>

class Ship
{
public:
	Ship( );
	~Ship();
	
	void Init(float X, float Y, float Z, const Texture Tex,
		const Direct3D &D3D);
	void Update(const KeyboardClient &Kbd, float DeltaTime);
	void Draw(Graphics &Gfx);

	DirectX::XMMATRIX GetWorld()const;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> &GetConstBuffer()const;

private:
	void SetPosition(float X, float Y, float Z);
	void SetTexture(const Texture Tex);

private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 orientation;
	DirectX::XMFLOAT3 scale;
	Model_Position_Texcoord mesh;
	// Constant buffer 
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer;
	// Texture
	Texture texture;
};

