#include "Model.h"

using namespace DirectX;
using namespace Microsoft::WRL;

// TODO: Load mesh from files
Model::Model()
{
	// There are different enums like point list, and line list.  There are also
	// enums for line strips and triangle strips, which connect the first and 
	// last points in the list.  Strips are also more efficient.
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

const Microsoft::WRL::ComPtr<ID3D11Buffer> &Model::GetVertexBuffer() const
{
	return vertex_buffer;
}

const Microsoft::WRL::ComPtr<ID3D11Buffer> &Model::GetIndexBuffer() const
{
	return index_buffer;
}

D3D11_PRIMITIVE_TOPOLOGY Model::GetTopology( ) const
{
	return topology;
}
