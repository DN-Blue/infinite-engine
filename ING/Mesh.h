#ifndef MESH_H
#define MESH_H

#include "INGLib.h"
#include <vector>

namespace Infinite {

	struct Vertex;

	struct MeshBuffers {
		ID3D11Buffer* pVertexBuffer;
		ID3D11Buffer* pIndexBuffer;
	};

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<UINT> indices;
	};


	class Mesh {
	public:
		Mesh();
		~Mesh();
	
	public:
		MeshBuffers buffers;
		MeshData* pData;

	};

}



#endif