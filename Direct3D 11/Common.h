#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <memory>

#define DXGI_FORMAT_FLOAT3		DXGI_FORMAT_R32G32B32_FLOAT
#define DXGI_FORMAT_FLOAT2		DXGI_FORMAT_R32G32_FLOAT						  
#define DXGI_FORMAT_FLOAT4		DXGI_FORMAT_R32G32B32A32_FLOAT
#define BGRA_PIXEL_FORMAT		DXGI_FORMAT_B8G8R8A8_UNORM
#define RGBA_PIXEL_FORMAT		DXGI_FORMAT_R8G8B8A8_UNORM
#define DEPTH_STENCIL_FORMAT	DXGI_FORMAT_D24_UNORM_S8_UINT
#define INDEX_BUFFER_FORMAT		DXGI_FORMAT_R32_UINT
#define POSITION_SEMANTIC		"POSITION"
#define TEXCOORD_SEMANTIC		"TEXCOORD"
#define NORMAL_SEMANTIC			"NORMAL"

namespace DirectX
{
	// Struct for shader creation														
	struct Blob
	{
		Blob( )
			:
			data(nullptr),
			length( 0 ),
			can_delete(true)
		{}
		Blob( Blob && B )
			:
			data( B.data ),
			length( B.length ),
			can_delete(B.can_delete)
		{
			B.data = nullptr;
			B.length = 0;
		}
		Blob( char *Data, UINT DataLength )
			:
			data( Data ),
			length( DataLength ),
			can_delete(false)
		{

		}
		Blob( UINT DataLength )
			:
			data( new char[ DataLength ] ),
			length( DataLength ),
			can_delete(true)
		{}
		Blob(ID3DBlob *B)
			:
			data(reinterpret_cast<char*>(B->GetBufferPointer())),
			length(B->GetBufferSize()),
			can_delete(false)
		{

		}
		Blob &operator=( Blob &&B )
		{
			Reset( std::move( B ) );
			return *this;
		}		
		UINT Length( )const
		{
			return length;
		}
		char *Data( )const
		{
			return data;
		}
		char*const*GetAddressOf( )const
		{
			return &data;
		}
		void Reset( Blob &&B )
		{
			data = B.data;
			length = B.length;
			can_delete = B.can_delete;

			B.data = nullptr;
		}
		void Release( )
		{
			if (can_delete)
			{
				if (data)
				{
					delete data, length;
					data = nullptr;
				}
			}
		}
		template<class T> const T *As( )const
		{
			return reinterpret_cast< T* >( data );
		}

		~Blob( )
		{
			Release( );
		}
	private:
		Blob( const Blob &B ) = delete;
		Blob &operator=( const Blob &B ) = delete;

	private:
		char* data;
		UINT length;
		bool can_delete;
	};
	// Common constant buffers for shaders

	// Vertex constant buffer
	_declspec(align(16)) struct TransformBuffer
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
	inline D3D11_INPUT_ELEMENT_DESC CreateElementDesc( LPSTR ElementType,
													   UINT SemanticIndex, DXGI_FORMAT Format, UINT SlotNumber = 0,
													   UINT Offset = D3D11_APPEND_ALIGNED_ELEMENT,
													   D3D11_INPUT_CLASSIFICATION Classification = D3D11_INPUT_PER_VERTEX_DATA,
													   UINT InstanceStepRate = 0 )
	{

		return{ ElementType, SemanticIndex, Format, SlotNumber, Offset,
			Classification, InstanceStepRate };
	}

	inline D3D11_INPUT_ELEMENT_DESC CreatePositionElement( )
	{
		return CreateElementDesc( POSITION_SEMANTIC, 0, DXGI_FORMAT_FLOAT3 );
	}

	inline D3D11_INPUT_ELEMENT_DESC CreateTexcoordElement( UINT TextureIndex = 0 )
	{
		assert( TextureIndex < 8 );
		return CreateElementDesc( TEXCOORD_SEMANTIC, TextureIndex, DXGI_FORMAT_FLOAT2 );
	}

	inline D3D11_INPUT_ELEMENT_DESC CreateNormalElement( )
	{
		return CreateElementDesc( NORMAL_SEMANTIC, 0, DXGI_FORMAT_FLOAT3 );
	}
}
