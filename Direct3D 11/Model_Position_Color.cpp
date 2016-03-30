#include "Model_Position_Color.h"

using namespace DirectX;
using namespace Microsoft::WRL;

void Model_Position_Color::CreatePlane(const Direct3D & D3D)
{
	ComPtr<ID3D11DeviceContext> context = D3D.GetContext();

	// Top left vertex
	XMFLOAT3 v_pos_0 = { -1.0f, 1.0f, 1.0f };
	// Top right vertex
	XMFLOAT3 v_pos_1 = { 1.0f, 1.0f, 1.0f };
	// Bottom left vertex
	XMFLOAT3 v_pos_2 = { -1.0f, -1.0f, 1.0f };
	// Bottom right vertex
	XMFLOAT3 v_pos_3 = { 1.0f, -1.0f, 1.0f };

	// Color
	XMFLOAT4 color = { 0.75f, 0.1f, 0.1f, 1.0f };
	// Use the vertices and texture coordinates to fill the vertex buffers
	Vertex vert;
	vert.position = v_pos_0;
	vert.color = color;
	vertices.push_back(vert);

	vert.position = v_pos_1;
	vert.color = color;
	vertices.push_back(vert);

	vert.position = v_pos_2;
	vert.color = color;
	vertices.push_back(vert);

	vert.position = v_pos_2;
	vert.color = color;
	vertices.push_back(vert);

	vert.position = v_pos_1;
	vert.color = color;
	vertices.push_back(vert);

	vert.position = v_pos_3;
	vert.color = color;
	vertices.push_back(vert);

	// Create the vertex buffer using the vector of vertices
	Vertex *pVertices = vertices.data();
	vertex_buffer = D3D.CreateVertexBuffer(static_cast<int>(vertices.size()),
		static_cast<int>(sizeof(Vertex)),
		reinterpret_cast<void**>(&pVertices));

	// The vertices are in the correct order to be rendered, so we can just use
	// sequential numbers from 0-5 since there are six vertices
	std::vector<DWORD> indices{ 0,1,2,3,4,5 };
	DWORD *pIndices = indices.data();

	// Create the index buffer
	index_buffer = D3D.CreateIndexBuffer(6, sizeof(DWORD),
		reinterpret_cast<void**>(&pIndices));

}

size_t Model_Position_Color::GetVertexCount() const
{
	return vertices.size();
}
