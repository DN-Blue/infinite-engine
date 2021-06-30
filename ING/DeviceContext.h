#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

#include "INGLib.h"

namespace Infinite {

	class Graphics;

	struct Shader;

	struct RasterizerState;

	struct DepthBufferState;

	class DeviceContext {
	public:
		DeviceContext(ID3D11DeviceContext* pImmContext);
		~DeviceContext();

	public:
		ID3D11DeviceContext* pImmContext;

	public:
		D3D11_VIEWPORT screenViewport;

	public:
		Graphics* pGraphics;

	public:
		void ClearRenderTargetView(float color[]);
		void DrawIndicesList(UINT vertex_count, UINT start_vertex_index);
		void SetViewPortSize(UINT width, UINT height);
		void SetShader(Shader* pShader);
		void SetRSState(RasterizerState* pRSState);
		void RegisterRSState(RasterizerState* pRSState);
		void SetDBState(DepthBufferState* pDBState);
		void RegisterDBState(DepthBufferState* pDBState);
	};

}


#endif