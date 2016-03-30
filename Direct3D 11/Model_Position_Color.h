#pragma once
#include "Common.h"
#include "Model.h"

class Model_Position_Color:public Model
{
public:
	struct Vertex: DirectX::Vertex_Position, DirectX::Vertex_Color
	{		
		// Struct intentionally left blank, gets it's members
		// through inheritance.
	};

	void CreatePlane(const Direct3D &D3D);
	size_t GetVertexCount()const;

private:
	// store vertices for collision calculations
	std::vector<Vertex> vertices;
};

