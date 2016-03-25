#pragma once
#include "Shader.h"

class Shader_Sprite :
	public Shader
{
public:
	Shader_Sprite(const Direct3D &D3D);
	~Shader_Sprite();
	void LoadShaderFiles(const std::string &VertexShaderFilename,
		const std::string &PixelShaderFilename,
		const Microsoft::WRL::ComPtr<ID3D11Device> &Device) override;
	void Set( Graphics &Gfx );
	const Microsoft::WRL::ComPtr<ID3D11SamplerState> &GetSampler( )const;
private:
	void Initialize(const DirectX::Blob &VertexBlob,
		const DirectX::Blob &PixelBlob,
		const Microsoft::WRL::ComPtr<ID3D11Device> &Device) override;

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

