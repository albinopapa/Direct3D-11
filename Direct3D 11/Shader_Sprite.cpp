#include "Shader_Sprite.h"
#include <vector>


Shader_Sprite::Shader_Sprite(const Direct3D &D3D)
	:
	Shader(D3D)
{
}


Shader_Sprite::~Shader_Sprite()
{
}

void Shader_Sprite::Initialize(
	const DirectX::Blob &VertexBlob, const DirectX::Blob &PixelBlob, 
	const Microsoft::WRL::ComPtr<ID3D11Device> &Device)
{	
	HRESULT hr = Device->CreateVertexShader(VertexBlob.Data(), 
											 VertexBlob.Length(), nullptr, 
											 vertex_shader.GetAddressOf());
	assert( SUCCEEDED( hr ) );

	hr = Device->CreatePixelShader(PixelBlob.Data(), PixelBlob.Length(),
									nullptr, pixel_shader.GetAddressOf());
	assert( SUCCEEDED( hr ) );

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied
	{
		DirectX::CreatePositionElement(),
		DirectX::CreateTexcoordElement()
	};

	hr = Device->CreateInputLayout(ied.data(), ied.size(), VertexBlob.Data( ),
									VertexBlob.Length( ), layout.GetAddressOf());
	assert( SUCCEEDED( hr ) );

	CD3D11_SAMPLER_DESC sd( D3D11_DEFAULT );

	hr = Device->CreateSamplerState( &sd, sampler.GetAddressOf( ) );
	assert( SUCCEEDED( hr ) );
}

void Shader_Sprite::LoadShaderFiles(const std::wstring & VertexShaderFilename,
	const std::wstring & PixelShaderFilename,
	const Microsoft::WRL::ComPtr<ID3D11Device> &Device)
{
	DirectX::Blob v_blob( LoadShaderFile( VertexShaderFilename ) );
	DirectX::Blob p_blob( LoadShaderFile( PixelShaderFilename ) );	
	Initialize( v_blob, p_blob, Device );
}

void Shader_Sprite::Set( Graphics & Gfx )
{
	Gfx.SetInputLayout( layout );
	Gfx.SetPixelShader( pixel_shader );
	Gfx.SetPixelSampler( sampler );
	Gfx.SetVertexShader( vertex_shader );
}

const Microsoft::WRL::ComPtr<ID3D11SamplerState>& Shader_Sprite::GetSampler( ) const
{
	return sampler;
}
