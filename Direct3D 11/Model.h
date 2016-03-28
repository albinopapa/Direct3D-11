#pragma once
#include "Common.h"
#include "Direct3D.h"
#include <vector>


class Model_Position_Texcoord
{
public:
	struct Vertex :DirectX::Vertex_Position, DirectX::Vertex_Texture
	{
		// Struct intentionally left blank, gets it's members
		// through inheritance.
	};

	Model_Position_Texcoord();

	void CreatePlane(const Direct3D &D3D);
	size_t GetVertexCount( )const;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> & GetVertexBuffer()const;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> & GetIndexBuffer()const;
	D3D11_PRIMITIVE_TOPOLOGY GetTopology( )const;

private:
	// store vertices for collision calculations
	std::vector<Vertex> vertices;
	// Buffer to hold the vertices
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
	// Buffer to hold the indices of the vertices
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
	// Enum to tell Direct3D how to render the object
	D3D11_PRIMITIVE_TOPOLOGY topology;
};

