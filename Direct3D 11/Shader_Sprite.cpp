#include "Shader_Sprite.h"



Shader_Sprite::Shader_Sprite(const Direct3D &D3D)
	:
	Shader(D3D)
{
}


Shader_Sprite::~Shader_Sprite()
{
}

void Shader_Sprite::Initialize(const DirectX::Blob &VertexBlob,
	const DirectX::Blob &PixelBlob,
	const Microsoft::WRL::ComPtr<ID3D11Device> &Device)
{
	Device->CreateVertexShader(VertexBlob.data.get(), VertexBlob.data_size, nullptr,
		vertex_shader.GetAddressOf());

	Device->CreatePixelShader(PixelBlob.data.get(), PixelBlob.data_size, nullptr,
		pixel_shader.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC ied[]
	{
		DirectX::CreatePositionElement(),
		DirectX::CreateTexcoordElement(0)
	};

	int ied_count = 2;

	Device->CreateInputLayout(ied, ied_count, VertexBlob.data.get(), 
		VertexBlob.data_size, layout.GetAddressOf());
	
	CD3D11_SAMPLER_DESC sd( D3D11_DEFAULT );

	HRESULT hr = Device->CreateSamplerState( &sd, sampler.GetAddressOf( ) );
	assert( SUCCEEDED( hr ) );
}

void Shader_Sprite::LoadShaderFiles(const std::string & VertexShaderFilename, 
	const std::string & PixelShaderFilename,
	const Microsoft::WRL::ComPtr<ID3D11Device> &Device)
{
	std::ifstream v_file(VertexShaderFilename, std::ios::ate | std::ios::binary);
	assert( v_file.is_open( ) );

	int file_size = v_file.tellg();
	v_file.seekg(std::ios::beg);

	DirectX::Blob v_blob;
	v_blob.data.reset(new char[file_size]);
	v_blob.data_size = file_size;
	v_file.read(v_blob.data.get(), file_size);

	std::ifstream p_file(PixelShaderFilename, std::ios::ate | std::ios::binary);
	assert( p_file.is_open( ) );

	file_size = p_file.tellg();
	p_file.seekg( std::ios::beg );

	DirectX::Blob p_blob;
	p_blob.data.reset(new char[file_size]);
	p_blob.data_size = file_size;
	p_file.read(p_blob.data.get(), file_size);

	Initialize(v_blob, p_blob, Device);

	v_file.close();
	p_file.close();
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
