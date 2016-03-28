#include "Shader.h"

Shader::Shader(const Direct3D &D3D)
:
context(D3D.GetContext())
{
}

Shader::~Shader()
{
}

void Shader::UpdateVertexConstBuffer(int BufferSize, void * BufferData, 
	const Microsoft::WRL::ComPtr<ID3D11Buffer>& ConstBuffer)
{
	assert(BufferData != nullptr && ConstBuffer.Get() != nullptr);

	D3D11_MAPPED_SUBRESOURCE ms{};
	HRESULT hr = context->Map(ConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
	assert( SUCCEEDED( hr ) );

	CopyMemory(ms.pData, BufferData, BufferSize);
	context->Unmap(ConstBuffer.Get(), 0);
}

DirectX::Blob Shader::LoadShaderFile( const std::wstring & Filename )
{	
	// Open shader file at the end (ate) and in binary mode
	std::ifstream shader_file( Filename, std::ios::ate | std::ios::binary );
	assert( shader_file.is_open( ) );
	
	// Get length of file using the get pointer position, then return to beginning
	int file_size = static_cast<int>( shader_file.tellg( ) );
	shader_file.seekg( std::ios::beg );

	// Read data from file and store the size into the Blob object
	DirectX::Blob shader_blob(file_size);
	shader_file.read( shader_blob.Data( ), file_size );
	
	// Close file
	shader_file.close( );

	return std::move(shader_blob);
}
