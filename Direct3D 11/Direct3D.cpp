#include "Direct3D.h"
#include <assert.h>

Direct3D::Direct3D(const Window &Win)
{
	InitDeviceAndSwapchain(Win);
	InitRenderTargetAndDepthViews(Win.GetWidth(), Win.GetHeight());
}

Direct3D::~Direct3D()
{
}

ID3D11Texture2D * Direct3D::CreateTexture(int Width, int Height, 
	DXGI_FORMAT Format, D3D11_BIND_FLAG Flag, BYTE ** ppInitialData)const
{
	// Describe the texture to Direct3D
	D3D11_TEXTURE2D_DESC td{};
	td.ArraySize = 1;
	td.MipLevels = 1;
	td.BindFlags = Flag;
	td.Format = Format;
	td.SampleDesc = { 1,0 };
	td.Usage = D3D11_USAGE_DEFAULT;
	td.Width = Width;
	td.Height = Height;
	
	// If creating a blank texture, the create function needs a nullptr
	// for the second parameter, otherwise, fill out the sub-resource
	// data structure
	D3D11_SUBRESOURCE_DATA srd{};
	D3D11_SUBRESOURCE_DATA *pSrd = nullptr;
	if (ppInitialData)
	{
		if (*ppInitialData)
		{
			srd.pSysMem = *ppInitialData;
			srd.SysMemPitch = Width * sizeof(UINT);
			srd.SysMemSlicePitch = srd.SysMemPitch * Height;
			pSrd = &srd;
		}
	}

	// Create the texture using the description, the sub-resource data
	// and the address of a texture and return the created texture;
	ID3D11Texture2D * texture = nullptr;
	HRESULT hr = device->CreateTexture2D(&td, pSrd, &texture);
	
	// Check that the texture was created
	assert(SUCCEEDED(hr));
	return texture;
}

ID3D11Buffer * Direct3D::CreateVertexBuffer(int ElementCount, int SizeOfElement,
	void** ppInitialData)const
{
	UINT size = ElementCount * SizeOfElement;

	D3D11_BUFFER_DESC bd{};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = size;
	bd.StructureByteStride = SizeOfElement;
	bd.Usage = D3D11_USAGE_DEFAULT;

	return CreateBuffer(bd, ppInitialData);
}

ID3D11Buffer * Direct3D::CreateIndexBuffer(int ElementCount, int SizeOfElement, 
	void ** ppInitialData)const
{
	UINT size = ElementCount * SizeOfElement;

	D3D11_BUFFER_DESC bd{};
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.ByteWidth = size;
	bd.StructureByteStride = SizeOfElement;
	bd.Usage = D3D11_USAGE_DEFAULT;
	
	return CreateBuffer(bd, ppInitialData);
}

ID3D11Buffer * Direct3D::CreateConstantBuffer(int ElementCount, int SizeOfElement, 
	void ** ppInitialData)const
{	
	UINT size = ElementCount * SizeOfElement;
	assert( size % 16 == 0 );

	D3D11_BUFFER_DESC bd{};
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = size;
	bd.StructureByteStride = SizeOfElement;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.Usage = D3D11_USAGE_DYNAMIC;

	return CreateBuffer(bd, ppInitialData);
}

ID3D11ShaderResourceView * Direct3D::CreateShaderResource(ID3D11Texture2D * Resource)const
{
	// Get the description of the texture resouce
	D3D11_TEXTURE2D_DESC td{};
	Resource->GetDesc(&td);
	
	// Fill out the shader resource view description, use the texture
	// description to get the format of the resource
	D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{};
	srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Format = td.Format;	
	
	// Create the shader resource
	ID3D11ShaderResourceView *srv = nullptr;
	HRESULT hr = device->CreateShaderResourceView(Resource, nullptr, &srv);
	assert(SUCCEEDED(hr));

	return srv;
}

ID3D11DepthStencilState * Direct3D::CreateDepthStencilState(
	D3D11_DEPTH_STENCIL_DESC * DS_Desc )const
{																  
	// The state of the depth buffer
	ID3D11DepthStencilState *depth_state;
	CD3D11_DEPTH_STENCIL_DESC ds_dec( D3D11_DEFAULT );
	if( !DS_Desc )
	{
		DS_Desc = &ds_dec;
	}

	HRESULT hr = device->CreateDepthStencilState( DS_Desc, &depth_state );
	assert( SUCCEEDED( hr ) );

	return depth_state;
}

const Microsoft::WRL::ComPtr<ID3D11Device> &Direct3D::GetDevice() const
{
	return device;
}

const Microsoft::WRL::ComPtr<ID3D11DeviceContext> &Direct3D::GetContext() const
{
	return context;
}

const Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &Direct3D::GetRenderTarget() const
{
	return rtv;
}

const Microsoft::WRL::ComPtr<ID3D11DepthStencilView> &Direct3D::GetDepthStencilView() const
{
	return dsv;
}

const Microsoft::WRL::ComPtr<IDXGISwapChain> &Direct3D::GetSwapChain() const
{
	return swapchain;
}
#if _DEBUG
const Microsoft::WRL::ComPtr<ID3D11Debug>& Direct3D::GetDebug( ) const
{
	return debug;
}
#endif
void Direct3D::InitDeviceAndSwapchain(const Window & Win)
{
	// Describe the swap chain to Direct3D
	DXGI_SWAP_CHAIN_DESC scd{};
	// 1 back buffer
	scd.BufferCount = 1;
	// BGRA color channel order 
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	// Refresh rate, numerator = 60, denominator = 1 -> 60 Hz
	scd.BufferDesc.RefreshRate = { 60, 1 };
	// Set scaling
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	// Set scanline order
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	// Assign the swap chain as a render target
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	
	// Allow user to press Alt+F4 to switch between windowed and full screen
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// Handle to the window, since we didn't specify the size, Direct3D will get 
	// it from the window handle
	scd.OutputWindow = Win.GetHandle();
	// Sample description, count = 1, quality = 0 -> default minimum
	scd.SampleDesc = { 1, 0 };
	// Tell Direct3D what to do to swap the back and front buffers
	// Discard means to discard the previous data and overwrite
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	// Setting windowed mode TRUE for windowed, FALSE for full screen
	scd.Windowed = TRUE;

	int device_params = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if _DEBUG
	device_params |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// Parameter descriptions for D3D11CreateDeviceAndSwapChain
	/*
	 1)		Use default display adapter
	 2)		Use hardware driver 
	 3)		Don't use software device
	 4)		Creation flags to support Direct2D interoperability...for DirectWrite,
			Direct3D runs faster in single threaded if you let it know to use single 
			threaded code
	 5)		Use default array of feature levels, from 11.0 to 9.1 to check which 
			version users video card supports
	 6)		Number of levels in array, if array was nullptr, pass 0
	 7)		DirectX SDK Version, D3D11_SDK_VERSION
	 8)		Address of swapchain description
	 9)		Address of swapchain
	 10)	Address of device
	 11)	Returns the highest feature level chosen that the users video card 
			supports
	 12)	Address of the device context
	*/
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		device_params,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		swapchain.GetAddressOf(),
		device.GetAddressOf(),
		&current_level,
		context.GetAddressOf()
		);

	assert(SUCCEEDED(hr));

#if _DEBUG
	hr = device.As( &debug );	
#endif
}

void Direct3D::InitRenderTargetAndDepthViews(int Width, int Height)
{
	// Get the buffer from the swap chain using a 2d texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
	HRESULT hr = swapchain->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf()));
	assert(SUCCEEDED(hr));
	DXGI_SWAP_CHAIN_DESC scd{};
	swapchain->GetDesc( &scd );

	// Use the texture to initialize the render target view
	hr = device->CreateRenderTargetView(back_buffer.Get(), nullptr, rtv.GetAddressOf());
	assert(SUCCEEDED(hr));

	// Create a 2d texture resource to create the depth buffer
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_buffer;

	// Create a texture resource to use for the depth buffer
	D3D11_TEXTURE2D_DESC td{};
	td.Width = Width;
	td.Height = Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.SampleDesc = { 1, 0 };

	hr = device->CreateTexture2D(&td, nullptr, depth_buffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	// Use the new texture to initialize the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc{};
	dsv_desc.Format = td.Format;
	dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	hr = device->CreateDepthStencilView(depth_buffer.Get(), &dsv_desc, dsv.GetAddressOf());
	assert(SUCCEEDED(hr));
}

ID3D11Buffer * Direct3D::CreateBuffer(const D3D11_BUFFER_DESC & BuffDes, void ** ppInitialData)const
{
	D3D11_SUBRESOURCE_DATA srd{};
	D3D11_SUBRESOURCE_DATA *pSrd = nullptr;
	if (ppInitialData)
	{
		if (*ppInitialData)
		{
			srd.pSysMem = *ppInitialData;
			pSrd = &srd;
		}
	}

	ID3D11Buffer *buffer = nullptr;
	HRESULT hr = device->CreateBuffer(&BuffDes, pSrd, &buffer);

	assert(SUCCEEDED(hr));

	return buffer;
}
