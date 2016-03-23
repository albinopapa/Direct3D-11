#include "Graphics.h"



Graphics::Graphics(const Window &Win)
	:
	d3d(Win)
{
	context = d3d.GetContext();
	rtv = d3d.GetRenderTarget();
	dsv = d3d.GetDepthStencilView();
	swapchain = d3d.GetSwapChain();
}


Graphics::~Graphics()
{
}

void Graphics::BeginFrame(float A, float R, float G, float B)
{
	float color[4]{ A, R, G, B };
	context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, NULL);
	context->ClearRenderTargetView(rtv.Get(), color);
}

void Graphics::EndFrame()
{
	swapchain->Present(NULL, NULL);
}

void Graphics::SetViewport(const D3D11_VIEWPORT & Viewport)
{
	context->RSSetViewports(1, &Viewport);
}

void Graphics::SetInputLayout(const Microsoft::WRL::ComPtr<ID3D11InputLayout>& Layout)
{
	context->IASetInputLayout(Layout.Get());
}

void Graphics::SetVertexBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& VertexBuffer, UINT Stride, UINT Offset)
{
	context->IASetVertexBuffers(NULL, 1, VertexBuffer.GetAddressOf(), &Stride, &Offset);
}

void Graphics::SetIndexBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& IndexBuffer)
{
	context->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, NULL);
}

void Graphics::SetVertexSampler(const Microsoft::WRL::ComPtr<ID3D11SamplerState> Sampler)
{
	context->VSSetSamplers(NULL, 1, Sampler.GetAddressOf());
}

void Graphics::SetPixelSampler(const Microsoft::WRL::ComPtr<ID3D11SamplerState> Sampler)
{
	context->PSSetSamplers(NULL, 1, Sampler.GetAddressOf());
}

void Graphics::SetVertexConstantBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& ConstantBuffer)
{
	context->VSSetConstantBuffers(NULL, 1, ConstantBuffer.GetAddressOf());
}

void Graphics::SetPixelConstantBuffer(const Microsoft::WRL::ComPtr<ID3D11Buffer>& ConstantBuffer)
{
	context->PSSetConstantBuffers(NULL, 1, ConstantBuffer.GetAddressOf());
}

void Graphics::SetVertexShaderResource(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& SRV)
{
	context->VSSetShaderResources(NULL, 1, SRV.GetAddressOf());
}

void Graphics::SetPixelShaderResource(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& SRV)
{
	context->PSSetShaderResources(NULL, 1, SRV.GetAddressOf());
}

void Graphics::SetVertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& VertexShader)
{
	context->VSSetShader(VertexShader.Get(), nullptr, NULL);
}

void Graphics::SetPixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& PixelShader)
{
	context->PSSetShader(PixelShader.Get(), nullptr, NULL);
}


