#include "Ship.h"

using namespace DirectX;

Ship::Ship()
	:
	position(0.0f, 0.0f, 0.0f),
	orientation(0.0f, 0.0f, 0.0f, 0.0f),
	scale(10.0f, 10.0f, 1.0f)
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

void Ship::Update(const KeyboardClient &Kbd, float DeltaTime)
{
	const float const_speed = 0.1f;
	XMFLOAT3 temp = position;

	if (Kbd.KeyPressed(VK_LEFT))
	{
		temp.x -= const_speed;
	}
	else if(Kbd.KeyPressed(VK_RIGHT))
	{
		temp.x += const_speed;
	}
	if (Kbd.KeyPressed(VK_UP))
	{
		temp.y += const_speed;
	}
	else if (Kbd.KeyPressed(VK_DOWN))
	{
		temp.y -= const_speed;
	}
	if (Kbd.KeyPressed(VK_ADD))
	{
		scale.x += 0.1f;
		scale.y += 0.1f;
	}
	else if (Kbd.KeyPressed(VK_SUBTRACT))
	{
		scale.x -= 0.1f;
		scale.y -= 0.1f;
	}

	// TODO: Get min/max from screen clip rect or bounding view frustum
	// Clip rect for 2D renders, BoundingFrustum for 3D renders
	temp.x = max(-400.0f + 8, min(temp.x, 399.0f - 8));
	temp.y = max(-300.0f + 12, min(temp.y, 299.0f - 12));
	scale.x = max(10.0f, min(100.0f, scale.x));
	scale.y = max(10.0f, min(100.0f, scale.y));

	position = temp;
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
	XMVECTOR mScal = XMLoadFloat3(&scale);

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
