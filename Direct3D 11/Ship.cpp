#include "Ship.h"

using namespace DirectX;

Ship::Ship( )
	:
	position( 0.0f, 0.0f, 0.0f ),
	orientation( 0.0f, 0.0f, 0.0f, 0.0f )
{}

Ship::Ship(const Direct3D &D3D)
	:
	texture( L"Images\\LightingTricks.png", D3D ),
	position( 0.0f, 0.0f, 10.0 ),
	orientation( 0.0f, 0.0f, 0.0f, 1.0f )
{
	mesh.CreatePlane( D3D );
	constant_buffer = D3D.CreateConstantBuffer( 1, sizeof( DirectX::TransformBuffer ) );
}


Ship::~Ship()
{
}

void Ship::Update(float DeltaTime)
{
	
}

DirectX::XMMATRIX Ship::GetWorld() const
{
	XMVECTOR mPos = XMLoadFloat3(&position);
	XMVECTOR mOri = XMLoadFloat4(&orientation);

	XMMATRIX translation = XMMatrixTranslationFromVector(mPos);
	XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(mOri);

	XMMATRIX world = rotation * translation;

	return world;
}

const Microsoft::WRL::ComPtr<ID3D11Buffer> &Ship::GetConstBuffer( )const
{
	return constant_buffer;
}

void Ship::Draw( Graphics &Gfx )
{
	Gfx.SetVertexBuffer( mesh.GetVertexBuffer( ), sizeof( Model_Position_Texcoord::Vertex ) );
	Gfx.SetIndexBuffer( mesh.GetIndexBuffer( ) );
	Gfx.SetTopology( mesh.GetTopology( ) );
	Gfx.SetVertexConstantBuffer( constant_buffer );
	Gfx.SetPixelShaderResource( texture.GetResource( ) );

	Gfx.Render( mesh.GetVertexCount( ) );
}
