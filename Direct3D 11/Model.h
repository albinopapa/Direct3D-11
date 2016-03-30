#pragma once
#include "Common.h"
#include "Direct3D.h"
#include <vector>

class Model
{
public:
	Model();
	virtual void CreatePlane(const Direct3D &D3D) = 0;
	virtual size_t GetVertexCount()const = 0;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> & GetVertexBuffer()const;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> & GetIndexBuffer()const;
	D3D11_PRIMITIVE_TOPOLOGY GetTopology()const;
protected:
	// Buffer to hold the vertices
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
	// Buffer to hold the indices of the vertices
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
	// Enum to tell Direct3D how to render the object
	D3D11_PRIMITIVE_TOPOLOGY topology;
};

