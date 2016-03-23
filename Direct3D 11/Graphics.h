#pragma once
#include "Direct3D.h"

class Graphics
{
public:
	Graphics(const Window &Win);
	~Graphics();

	void BeginFrame(float A = 0, float R = 0, float G = 0, float B = 0);
	void EndFrame();
	
	void SetViewport(const D3D11_VIEWPORT &Viewport);
	void SetInputLayout(const Microsoft::WRL::ComPtr<ID3D11InputLayout> &Layout);
	void SetVertexBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer> &VertexBuffer,
		UINT Stride, UINT Offset = NULL);
	void SetIndexBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer> &IndexBuffer);
	void SetVertexSampler(const Microsoft::WRL::ComPtr<ID3D11SamplerState> Sampler);
	void SetPixelSampler(const Microsoft::WRL::ComPtr<ID3D11SamplerState> Sampler);
	void SetVertexConstantBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer> &ConstantBuffer);
	void SetPixelConstantBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer> &ConstantBuffer);
	void SetVertexShaderResource(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &SRV);
	void SetPixelShaderResource(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &SRV);
	void SetVertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader> &VertexShader);
	void SetPixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader> &PixelShader);
	
	void Render() {};
private:
	Direct3D d3d;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
};

