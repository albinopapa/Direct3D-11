#pragma once
#include "Window.h"
#include <wrl.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")


class Direct3D
{
public:
	Direct3D(const Window &Win);
	~Direct3D();

	ID3D11Texture2D *CreateTexture(int Width, int Height, DXGI_FORMAT Format, 
		D3D11_BIND_FLAG Flag, BYTE**ppInitialData = nullptr)const;
	ID3D11Buffer *CreateVertexBuffer(int ElementCount, int SizeOfElement,
		void** ppInitialData = nullptr)const;
	ID3D11Buffer *CreateIndexBuffer(int ElementCount, int SizeOfElement,
		void** ppInitialData = nullptr)const;
	ID3D11Buffer *CreateConstantBuffer(int ElementCount, int SizeOfElement,
		void** ppInitialData = nullptr)const;
	ID3D11ShaderResourceView *CreateShaderResource(ID3D11Texture2D *Resource)const;
	ID3D11DepthStencilState *CreateDepthStencilState( D3D11_DEPTH_STENCIL_DESC * DS_Desc = nullptr )const;
	const Microsoft::WRL::ComPtr<ID3D11Device> &GetDevice()const;
	const Microsoft::WRL::ComPtr<ID3D11DeviceContext> &GetContext()const;
	const Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &GetRenderTarget()const;
	const Microsoft::WRL::ComPtr<ID3D11DepthStencilView> &GetDepthStencilView()const;
	const Microsoft::WRL::ComPtr<IDXGISwapChain> &GetSwapChain()const;
#if _DEBUG
	const Microsoft::WRL::ComPtr<ID3D11Debug> &GetDebug( )const;
#endif
private:
	void InitDeviceAndSwapchain(const Window &Win);
	void InitRenderTargetAndDepthViews(int Width, int Height);
	ID3D11Buffer *CreateBuffer(const D3D11_BUFFER_DESC &BuffDes, 
		void** ppInitialData = nullptr)const;

private:
	// The device is used to allocate resources like textures and shaders
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	// The device context is the interface handling those resources, 
	// like calling the shaders
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	// The swap chain is the chain of display buffers
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	// The render target view can be a texture or the swap chain to render to
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
	// The depth stencil view is the texture that depth is rendered to.
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
#if _DEBUG
	// Debugger
	Microsoft::WRL::ComPtr<ID3D11Debug> debug;
#endif
	// Feature level helps determine code paths for different level of hardware
	D3D_FEATURE_LEVEL current_level;
};

