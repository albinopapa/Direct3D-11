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
#ifdef _DEBUG
	D3D11_BUFFER_DESC bd{};
	ConstBuffer->GetDesc(&bd);
	assert(bd.ByteWidth == BufferSize);
#endif
	D3D11_MAPPED_SUBRESOURCE ms{};
	context->Map(ConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
	DirectX::TransformBuffer *dst = ( DirectX::TransformBuffer * )ms.pData;
	DirectX::TransformBuffer *src = ( DirectX::TransformBuffer * )BufferData;

	CopyMemory(ms.pData, BufferData, BufferSize);
	context->Unmap(ConstBuffer.Get(), 0);
}
