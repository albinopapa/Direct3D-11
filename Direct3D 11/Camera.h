#pragma once
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "Direct3D.h"
#include "Window.h"

class Camera
{
public:
	Camera( );
	Camera( const Window &Win );
	~Camera();

	void Update(float DeltaTime);
	DirectX::XMMATRIX GetView()const;
	DirectX::XMMATRIX GetProjection(const Window &Win)const;
	const D3D11_VIEWPORT &GetViewport( )const;
private:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 orientation;
	float vertical_fov;
	D3D11_VIEWPORT viewport;
};

