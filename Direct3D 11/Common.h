#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <memory>

#define DXGI_FORMAT_FLOAT4 DXGI_FORMAT_R32G32B32A32_FLOAT
#define DXGI_FORMAT_FLOAT3 DXGI_FORMAT_R32G32B32_FLOAT
#define DXGI_FORMAT_FLOAT2 DXGI_FORMAT_R32G32_FLOAT
#define BGRA_PIXEL_FORMAT DXGI_FORMAT_B8G8R8A8_UNORM
#define RGBA_PIXEL_FORMAT DXGI_FORMAT_R8G8B8A8_UNORM
#define DEPTH_STENCIL_FORMAT DXGI_FORMAT_D24_UNORM_S8_UINT
#define INDEX_BUFFER_FORMAT DXGI_FORMAT_R32_UINT
#define POSITION_SEMANTIC "POSITION"
#define TEXCOORD_SEMANTIC "TEXCOORD"
#define NORMAL_SEMANTIC "NORMAL"

namespace DirectX
{
	// Struct for shader creation
	struct Blob
	{
		std::unique_ptr<char> data;
		UINT data_size;
	};
	// Common constant buffers for shaders

	// Vertex constant buffer
	struct alignas( 16 ) TransformBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	// Pixel constant buffer
	struct DirectionalLightBuffer
	{
		// xyz is position, w is intensity
		DirectX::XMFLOAT4 pos_intesity;
		DirectX::XMFLOAT4 color;
	};

	// Common mesh data structures
	struct Vertex_Position
	{
		DirectX::XMFLOAT3 position;
	};

	struct Vertex_Color
	{
		DirectX::XMFLOAT4 color;
	};

	struct Vertex_Texture
	{
		DirectX::XMFLOAT2 texcoord;
	};

	struct Vertex_Normal
	{
		DirectX::XMFLOAT3 normal;
	};

	// Input element description creation functions, input element descriptions
	// describe the layout of each vertex in a vertex buffer
	inline D3D11_INPUT_ELEMENT_DESC CreateElementDesc(LPSTR ElementType,
		UINT SemanticIndex, DXGI_FORMAT Format, UINT SlotNumber = 0,
		UINT Offset = D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_CLASSIFICATION Classification = D3D11_INPUT_PER_VERTEX_DATA,
		UINT InstanceStepRate = 0)
	{

		return{ ElementType, SemanticIndex, Format, SlotNumber, Offset,
			Classification, InstanceStepRate };
	}

	inline D3D11_INPUT_ELEMENT_DESC CreatePositionElement()
	{
		return CreateElementDesc(POSITION_SEMANTIC, 0, DXGI_FORMAT_FLOAT3);
	}

	inline D3D11_INPUT_ELEMENT_DESC CreateTexcoordElement(UINT TextureIndex = 0)
	{
		assert(TextureIndex < 8);
		return CreateElementDesc(TEXCOORD_SEMANTIC, TextureIndex, DXGI_FORMAT_FLOAT2);
	}

	inline D3D11_INPUT_ELEMENT_DESC CreateNormalElement()
	{
		return CreateElementDesc(NORMAL_SEMANTIC, 0, DXGI_FORMAT_FLOAT3);
	}
}
