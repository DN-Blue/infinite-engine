#include "ResourcesManager.h"
#include "Mesh.h"

using namespace Infinite;









MeshData* ResourcesManager::FBXImportMeshData(std::string path) {
	MeshData* pMesh = new MeshData();



	return pMesh;
}

Mesh* ResourcesManager::FBXImportMesh(std::string path) {
	Mesh* pMesh = new Mesh();
	pMesh->pData = FBXImportMeshData(path);
	return pMesh;
}