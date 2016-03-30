#pragma once
#include "Model.h"

class Model_Position_Texcoord :public Model
{
public:
	struct Vertex :DirectX::Vertex_Position, DirectX::Vertex_Texture
	{
		// Struct intentionally left blank, gets it's members
		// through inheritance.
	};

	Model_Position_Texcoord();
	void CreatePlane(const Direct3D &D3D);
	size_t GetVertexCount()const;

private:
	// store vertices for collision calculations
	std::vector<Vertex> vertices;
};

