#ifndef RENDERER_H
#define RENDERER_H

#include "INGLib.h"

namespace Infinite {

	class RenderSystem;

	class Mesh;

	struct Material;
	
	struct MeshBuffers;

	struct Shader;
	
	struct RasterizerState;

	struct DepthBufferState;

	class Renderer {
	public:
		Renderer();
		~Renderer();

	public:
		RenderSystem* pSystem;

		void RegisterMesh(Mesh* pMesh);

		void DrawMesh(Mesh* pMesh);

		void SetMaterial(Material* pMat);

		void UpdateMaterial(Material* pMat);

		void SetShader(Shader* pShader);

		void RegisterMaterial(Material* pMat);

		void Draw();

		void UseSolidRSState();
		void UseInverseSolidRSState();
		void UseNoCullSolidRSState();
		void UseWireframeRSState();

		void EnableDepth();
		void DisableDepth();

	public:
		Material* CreateTransformationMaterial();
		void UpdateTransformationMaterial(Material* pMat);

	public:
		Mesh* pMesh;
		Material* pMaterial;
		RasterizerState* pSolidRSState;
		RasterizerState* pInverseSolidRSState;
		RasterizerState* pNoCullSolidRSState;
		RasterizerState* pWireframeRSState;
		DepthBufferState* pEDepthBufferSate;
		DepthBufferState* pDDepthBufferSate;

	};

}


#endif