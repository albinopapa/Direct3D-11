#include "Ship.h"

using namespace DirectX;

Ship::Ship( )
	:
	position( 0.0f, 0.0f, 0.0f ),
	orientation( 0.0f, 0.0f, 0.0f, 0.0f )
{

}

Ship::~Ship()
{
}

void Ship::Init(float X, float Y, float Z, const Texture Tex,
	const Direct3D &D3D)
{
	mesh.CreatePlane(D3D);
	constant_buffer = D3D.CreateConstantBuffer(1, 
		sizeof(DirectX::TransformBuffer));
	SetPosition(X, Y, Z);
	SetTexture(Tex);
}

void Ship::Update(float DeltaTime)
{
	position.z += 0.01f;
}

void Ship::Draw(Graphics &Gfx)
{
	Gfx.SetVertexBuffer(mesh.GetVertexBuffer(), sizeof(Model_Position_Texcoord::Vertex));
	Gfx.SetIndexBuffer(mesh.GetIndexBuffer());
	Gfx.SetTopology(mesh.GetTopology());
	Gfx.SetPixelShaderResource(texture.GetResource());
	Gfx.SetVertexConstantBuffer(constant_buffer);

	Gfx.Render(mesh.GetVertexCount());
}

DirectX::XMMATRIX Ship::GetWorld() const
{
	XMVECTOR mPos = XMLoadFloat3(&position);
	XMVECTOR mOri = XMLoadFloat4(&orientation);
	XMVECTOR mScal = XMVectorSet( 100.0f, 100.0f, 10.0f, 1.0f );

	XMMATRIX translation = XMMatrixTranslationFromVector(mPos);
	XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(mOri);
	XMMATRIX scale = XMMatrixScalingFromVector( mScal );

	XMMATRIX world = rotation * scale * translation;

	return world;
}

const Microsoft::WRL::ComPtr<ID3D11Buffer> &Ship::GetConstBuffer( )const
{
	return constant_buffer;
}

void Ship::SetPosition(float X, float Y, float Z)
{
	position = XMFLOAT3(X, Y, Z);
}

void Ship::SetTexture(const Texture Tex)
{
	texture = Tex;
}
