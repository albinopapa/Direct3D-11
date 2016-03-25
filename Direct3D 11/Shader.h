#pragma once
#include "Direct3D.h"
#include <string>
#include <fstream>
#include <assert.h>
#include "Common.h"
#include "Graphics.h"

class Shader
{
public:

	Shader(const Direct3D &D3D);
	virtual ~Shader();

	virtual void LoadShaderFiles(const std::string &VertexShaderFilename,
		const std::string &PixelShaderFilename,
		const Microsoft::WRL::ComPtr<ID3D11Device> &Device) = 0;
	virtual void Set( Graphics &Gfx ) = 0;

	void UpdateVertexConstBuffer(int BufferSize, void *BufferData,
		const Microsoft::WRL::ComPtr<ID3D11Buffer> &ConstBuffer);

protected:
	virtual void Initialize(const DirectX::Blob &VertexBlob,
		const DirectX::Blob &PixelBlob,
		const Microsoft::WRL::ComPtr<ID3D11Device> &Device) = 0;

protected:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	// Layout of the vertex buffer
	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
	// Vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
	// Pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader;

};

