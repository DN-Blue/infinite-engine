#include "ResourcesManager.h"
#include "Mesh.h"
#include <fstream>

using namespace Infinite;









MeshData* ResourcesManager::IModelImportMeshData(std::string path) {
	MeshData* pMeshData = new MeshData();

	std::ifstream fin(path);

	if (!fin)
	{
		return nullptr;
	}

	UINT vcount = 0;
	UINT tcount = 0;
	std::string ignore;

	fin >> ignore >> vcount;
	fin >> ignore >> tcount;
	fin >> ignore >> ignore >> ignore >> ignore;

	pMeshData->vertices.resize(vcount);
	for (UINT i = 0; i < vcount; ++i)
	{
		fin >> pMeshData->vertices[i].position.x >> pMeshData->vertices[i].position.y >> pMeshData->vertices[i].position.z;
		fin >> pMeshData->vertices[i].normal.x >> pMeshData->vertices[i].normal.y >> pMeshData->vertices[i].normal.z;
	}

	fin >> ignore;
	fin >> ignore;
	fin >> ignore;

	UINT mSkullIndexCount = 3 * tcount;

	pMeshData->indices.resize(mSkullIndexCount);
	for (UINT i = 0; i < tcount; i++) {
		fin >> pMeshData->indices[i * 3 + 0] >> pMeshData->indices[i * 3 + 1] >> pMeshData->indices[i * 3 + 2];
	}

	fin.close();

	return pMeshData;
}

Mesh* ResourcesManager::IModelImportMesh(std::string path) {
	Mesh* pMesh = new Mesh();
	pMesh->pData = FBXImportMeshData(path);
	return pMesh;
}