#include "Camera.h"


using namespace DirectX;
Camera::Camera()
	:
	pos(XMFLOAT3(0.0f, 0.0f, -5.0f)),
	orientation(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)),
	vertical_fov(XMConvertToRadians(70)),
	viewport( { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f } )
{

}

Camera::Camera( const Window & Win )
	:
	pos( XMFLOAT3( 0.0f, 0.0f, -5.0f ) ),
	orientation( XMFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f ) ),
	vertical_fov( XMConvertToRadians( 70 ) )
{
	viewport.Width = static_cast<float>( Win.GetWidth( ) );
	viewport.Height = static_cast<float>( Win.GetHeight( ) );
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.1f;
	viewport.MaxDepth = 1.0f;
}


Camera::~Camera()
{
}

void Camera::Update(float DeltaTime)
{
	//pos.x += DeltaTime;
}

XMMATRIX Camera::GetView() const
{
	XMVECTOR mPos = XMLoadFloat3(&pos);
	XMVECTOR mOri = XMLoadFloat4(&orientation);

	XMMATRIX translation = XMMatrixTranslationFromVector(mPos);
	XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(mOri);

	XMMATRIX world = rotation * translation;
	XMMATRIX view = XMMatrixInverse(nullptr, world);

	return view;
}

DirectX::XMMATRIX Camera::GetProjection(const Window &Win) const
{
	// TODO: Test h / w and w / h to see what the results are.
	// Function asks for h / w
	float height = static_cast<float>(Win.GetHeight());
	float width = static_cast<float>(Win.GetWidth());

	float screen_ratio = height / width;
	XMMATRIX projection = XMMatrixOrthographicLH(viewport.Width, 
		viewport.Height, 1.0f, 100.0f);
	/*XMMATRIX projection = XMMatrixPerspectiveFovLH(
		vertical_fov, screen_ratio, 0.1f, 100.0f);*/
	return projection;
}

const D3D11_VIEWPORT & Camera::GetViewport( ) const
{
	return viewport;
}

