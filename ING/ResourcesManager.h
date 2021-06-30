#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include "INGLib.h"


namespace Infinite {

	class Mesh;
	
	struct MeshData;

	class ResourcesManager {
	public:
		ResourcesManager();
		~ResourcesManager();
	
	public:
		ING* pING;

	public:
		bool Init();


		Mesh* FBXImportMesh(std::string path);
		MeshData* FBXImportMeshData(std::string path);

		Mesh* IModelImportMesh(std::string path);
		MeshData* IModelImportMeshData(std::string path);
	
	};
}

#endif