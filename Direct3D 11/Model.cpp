#include "Model.h"

using namespace DirectX;
using namespace Microsoft::WRL;

// TODO: Load mesh from files
Model_Position_Texcoord::Model_Position_Texcoord()
{
	// There are different enums like point list, and line list.  There are also
	// enums for line strips and triangle strips, which connect the first and 
	// last points in the list.  Strips are also more efficient.
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void Model_Position_Texcoord::CreatePlane(const Direct3D & D3D)
{
	ComPtr<ID3D11DeviceContext> context = D3D.GetContext();
	
	// Top left vertex
	XMFLOAT3 v_pos_0 = { -1.0f, 1.0f, 1.0f };
	XMFLOAT2 t_pos_0 = { 0.0f, 0.0f };
	// Top right vertex
	XMFLOAT3 v_pos_1 = { 1.0f, 1.0f, 1.0f };
	XMFLOAT2 t_pos_1 = { 1.0f, 0.0f };
	// Bottom left vertex
	XMFLOAT3 v_pos_2 = { -1.0f, -1.0f, 1.0f };
	XMFLOAT2 t_pos_2 = { 0.0f, 1.0f };
	// Bottom right vertex
	XMFLOAT3 v_pos_3 = { 1.0f, -1.0f, 1.0f };
	XMFLOAT2 t_pos_3 = { 1.0f, 1.0f };
	
	// Use the vertices and texture coordinates to fill the vertex buffers
	Vertex vert;
	vert.position = v_pos_0;
	vert.texcoord = t_pos_0;
	vertices.push_back(vert);
	
	vert.position = v_pos_1;
	vert.texcoord = t_pos_1;
	vertices.push_back(vert);

	vert.position = v_pos_2;
	vert.texcoord = t_pos_2;
	vertices.push_back(vert);

	vert.position = v_pos_2;
	vert.texcoord = t_pos_2;
	vertices.push_back(vert);

	vert.position = v_pos_1;
	vert.texcoord = t_pos_1;
	vertices.push_back(vert);

	vert.position = v_pos_3;
	vert.texcoord = t_pos_3;
	vertices.push_back(vert);

	// Create the vertex buffer using the vector of vertices
	Vertex *pVertices = vertices.data();
	vertex_buffer = D3D.CreateVertexBuffer(vertices.size(), sizeof(Vertex),
		reinterpret_cast<void**>(&pVertices));

	// The vertices are in the correct order to be rendered, so we can just use
	// sequential numbers from 0-5 since there are six vertices
	std::vector<DWORD> indices{ 0,1,2,3,4,5 };
	DWORD *pIndices = indices.data( );

	// Create the index buffer
	index_buffer = D3D.CreateIndexBuffer(6, sizeof(DWORD), 
		reinterpret_cast<void**>(&pIndices ));

}

UINT Model_Position_Texcoord::GetVertexCount( ) const
{
	return vertices.size();
}

ID3D11Buffer *Model_Position_Texcoord::GetVertexBuffer() const
{
	return vertex_buffer.Get();
}

ID3D11Buffer *Model_Position_Texcoord::GetIndexBuffer() const
{
	return index_buffer.Get();
}

D3D11_PRIMITIVE_TOPOLOGY Model_Position_Texcoord::GetTopology( ) const
{
	return topology;
}
