#pragma once
#include "Direct3D.h"


class Graphics
{
public:
	Graphics( const Direct3D &D3D, const Window &Win );
	~Graphics( );

	void BeginFrame( float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 1.0f );
	void EndFrame( );

	void SetTopology( D3D11_PRIMITIVE_TOPOLOGY Topology );
	void SetRenderTarget( );
	void SetRenderTarget( const Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &RenderTarget );
	void SetDepthState( );
	void SetDepthState( const Microsoft::WRL::ComPtr<ID3D11DepthStencilState> &DepthState, UINT StencilRef );
	void SetViewport( const D3D11_VIEWPORT &Viewport );
	void SetInputLayout( const Microsoft::WRL::ComPtr<ID3D11InputLayout> &Layout );
	void SetVertexBuffer( const Microsoft::WRL::ComPtr<ID3D11Buffer> &VertexBuffer,
						  UINT Stride, UINT Offset = NULL );
	void SetIndexBuffer( const Microsoft::WRL::ComPtr<ID3D11Buffer> &IndexBuffer );
	void SetVertexSampler( const Microsoft::WRL::ComPtr<ID3D11SamplerState> &Sampler );
	void SetPixelSampler( const Microsoft::WRL::ComPtr<ID3D11SamplerState> &Sampler );
	void SetVertexConstantBuffer( const Microsoft::WRL::ComPtr<ID3D11Buffer> &ConstantBuffer );
	void SetPixelConstantBuffer( const Microsoft::WRL::ComPtr<ID3D11Buffer> &ConstantBuffer );
	void SetVertexShaderResource( const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &SRV );
	void SetPixelShaderResource( const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &SRV );
	void SetVertexShader( const Microsoft::WRL::ComPtr<ID3D11VertexShader> &VertexShader );
	void SetPixelShader( const Microsoft::WRL::ComPtr<ID3D11PixelShader> &PixelShader );

	void Render( UINT VertexCount, UINT StartIndex = 0 );
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_enabled;
	Microsoft::WRL::ComPtr<ID3D11Debug> debug;
};

