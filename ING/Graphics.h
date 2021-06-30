#ifndef  GRAPHICS_H
#define GRAPHICS_H

#include "INGLib.h"

namespace Infinite {

	class ING;

	class DeviceContext;

	class RenderSystem;

	class SwapChain;

	class Mesh;

	struct Material;

	struct Shader;

	struct RasterizerState;

	class Graphics {

	public:
		Graphics();
		~Graphics();

	public:
		bool Init();
		
	private:
		bool InitDirectX();

	public:
		bool CreateVertexInputLayout(Shader* pShader);
		void RegisterShader(Shader* pShader);

	public:
		ING* pING;

	public:
		DeviceContext* pDeviceContext;
	
	public:
		SwapChain* pSwapChain;

	public:
		RenderSystem* pRenderSystem;




	public:
		ID3D11Device* pd3dDevice;
		D3D_FEATURE_LEVEL featureLevel;

	public:
		IDXGIDevice* pdxgiDevice;
		IDXGIAdapter* pdxgiAdapter;
		IDXGIFactory* pdxgiFactory;

	public:
		ID3D11Texture2D* mDepthStencilBuffer;
		ID3D11DepthStencilView* mDepthStencilView;

	public:
		void SetScreenSize(UINT width, UINT height);

	public:
		Shader* CreateShader(LPCWSTR srcPath);




		
	public:
		friend class Mesh;
		friend struct MeshBuffers;
		friend struct MeshData;
		friend class DeviceContext;
		friend class SwapChain;
		friend class RenderSystem;
		friend struct Material;
		friend struct Shader;
		friend struct Vertex;
		friend struct ConstantBufferInput;
		friend struct RasterizerState;

	};

};



#endif
